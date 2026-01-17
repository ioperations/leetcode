import time
import sys
import random

# ANSI Escape Codes
MOVE_UP = "\033[F"      # Move cursor to the beginning of the previous line
CLEAR_LINE = "\033[K"   # Clear the current line

def draw_progress_bar(label, percent, width=30):
    """Creates a string representing a single vertex/progress bar."""
    filled_length = int(width * percent // 100)
    bar = "█" * filled_length + "-" * (width - filled_length)
    status = "DONE" if percent >= 100 else f"{percent:3}%"
    return f"{label:<15} [{bar}] {status}"

def simulate_docker_pull():
    # Our "Vertices" (Initial state)
    layers = [
        {"id": "Layer 1 (452MB)", "progress": 0, "speed": 1.5},
        {"id": "Layer 2 (121MB)", "progress": 0, "speed": 4.2},
        {"id": "Layer 3 (890MB)", "progress": 0, "speed": 0.8},
    ]

    print("--- Pulling Image: 'my-app:latest' ---")
    # Print empty lines first to reserve space for our vertices
    for _ in layers:
        print("")

    while any(l["progress"] < 100 for l in layers):
        # 1. Move cursor back up to the start of the vertex list
        sys.stdout.write(MOVE_UP * len(layers))

        for layer in layers:
            # 2. Update the progress logic
            if layer["progress"] < 100:
                layer["progress"] = min(100, layer["progress"] + layer["speed"] * random.uniform(0.5, 2.0))
            
            # 3. Clear the line and draw the updated vertex
            sys.stdout.write(CLEAR_LINE + draw_progress_bar(layer["id"], int(layer["progress"])) + "\n")
        
        sys.stdout.flush()
        time.sleep(0.1)

    print("\nDownload complete. Image is up to date.")

if __name__ == "__main__":
    simulate_docker_pull()
