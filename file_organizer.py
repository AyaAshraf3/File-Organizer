import sys
import shutil
import json
from pathlib import Path

CONFIG_FILE = "config.json"
UNDO_LOG = "undo_log.json"


def load_categories(config_path: Path):
    if not config_path.exists():
        print(f"Error: Config file {config_path} not found.")
        sys.exit(1)
    with open(config_path, "r") as f:
        config = json.load(f)
    # Convert lists to sets for faster lookup
    return {cat: set(exts) for cat, exts in config.get("categories", {}).items()}


def has_extension(file: Path, ext_list: set) -> bool:
    return file.suffix.lower() in ext_list


def organize_files(folder_path: Path, categories: dict, simulate: bool):
    counters = {cat: 0 for cat in categories.keys()}
    counters["Others"] = 0

    undo_moves = {}

    # Create category folders
    for category in counters.keys():
        (folder_path / category).mkdir(exist_ok=True)

    # Iterate over files
    for entry in folder_path.iterdir():
        if not entry.is_file():
            continue

        # Find matching category
        dest_folder = None
        for category, extensions in categories.items():
            if has_extension(entry, extensions):
                dest_folder = folder_path / category
                counters[category] += 1
                break

        if dest_folder is None:
            dest_folder = folder_path / "Others"
            counters["Others"] += 1

        dest = dest_folder / entry.name
        undo_moves[str(dest)] = str(entry)  # Record for undo

        if simulate:
            print(f"[SIMULATE] Move: {entry} -> {dest}")
        else:
            try:
                shutil.move(str(entry), str(dest))
            except Exception as e:
                print(f"Error moving file {entry}: {e}")

    if not simulate:
        with open(UNDO_LOG, "w") as f:
            json.dump(undo_moves, f, indent=4)

    # Print summary
    print("\nSummary:")
    for category, count in counters.items():
        print(f"{category}: {count}")


def undo_moves():
    if not Path(UNDO_LOG).exists():
        print("No undo log found.")
        return

    with open(UNDO_LOG, "r") as f:
        undo_data = json.load(f)

    for src, dest in undo_data.items():
        src_path = Path(src)
        dest_path = Path(dest)
        if src_path.exists():
            try:
                shutil.move(str(src_path), str(dest_path))
                print(f"Moved back: {src_path} -> {dest_path}")
            except Exception as e:
                print(f"Error undoing move for {src_path}: {e}")

    Path(UNDO_LOG).unlink()  # Remove log after undo


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <folder_path> [--simulate] [--undo]")
        sys.exit(1)

    if "--undo" in sys.argv:
        undo_moves()
        sys.exit(0)

    folder_path = Path(sys.argv[1])
    simulate = "--simulate" in sys.argv

    if not folder_path.exists() or not folder_path.is_dir():
        print("Error: Provided path is not a valid directory.")
        sys.exit(1)

    categories = load_categories(Path(CONFIG_FILE))
    organize_files(folder_path, categories, simulate)
