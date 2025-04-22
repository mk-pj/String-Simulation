import os
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter


def animate_displacement(csv_path, output_path, fps=10):
    df = pd.read_csv(csv_path)

    point_count = (df.shape[1] - 1) // 5
    indices = list(range(point_count))

    fig, ax = plt.subplots(figsize=(10, 5))
    line, = ax.plot([], [], 'b-', lw=2)
    ax.set_xlim(0, point_count - 1)
    ax.set_ylim(-1e-4, 1e-4)
    ax.set_xlabel("i (point)")
    ax.set_ylabel("y [m]")
    ax.set_title("String displacement animation")

    def init():
        line.set_data([], [])
        return line,

    def update(frame):
        y = [df[f"y{i}"][frame] for i in indices]
        line.set_data(indices, y)
        ax.set_title(f"Time: {df['t'][frame]:.2f} s")
        return line,

    anim = FuncAnimation(fig, update, frames=len(df), init_func=init, blit=True)

    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    anim.save(output_path, writer=PillowWriter(fps=fps))
    plt.close()
    print(f"Saved as: {output_path}")


if __name__ == '__main__':
    animate_displacement("../data/pos1.csv", "../charts/displacement.gif", fps=10)
