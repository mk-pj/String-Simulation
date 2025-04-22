import os
import pandas as pd
import matplotlib.pyplot as plt


def pos():
    df = pd.read_csv("../data/pos1.csv")
    point_count = (df.shape[1] - 1) // 5
    indices = [df[f"i{i}"][0] for i in range(point_count)]

    plt.figure(figsize=(12, 6))
    for _, row in df.iterrows():
        t = row["t"]
        y = [row[f"y{i}"] for i in range(point_count)]
        plt.plot(indices, y, label=f"t = {t:.2f}", alpha=0.4)

    plt.title("The shape of the string")
    plt.xlabel("i [point]")
    plt.xticks([2*i for i in range(0, 26)])
    plt.ylabel("y [m]")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig("../charts/string_shape.png")


def energy():
    df = pd.read_csv("../data/energy2.csv")
    plt.figure(figsize=(12, 6))
    plt.plot(df["t"], df["Ek"], label=f"kinetic energy")
    plt.plot(df["t"], df["Ep"], label=f"potential energy")
    plt.plot(df["t"], df["Ec"], label=f"total energy")
    plt.title("Energy plot")
    plt.xlabel("t [s]")
    plt.ylabel("E [J]")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig("../charts/energy.png")


def main():
    os.makedirs("../charts", exist_ok=True)
    pos()
    energy()


if __name__ == '__main__':
    main()