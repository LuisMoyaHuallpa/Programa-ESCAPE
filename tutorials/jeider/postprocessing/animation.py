"""Figure each timestep."""
import csv
import matplotlib.pyplot as plt
import os
from matplotlib.animation import FuncAnimation

pathMeshLink = "../meshLink/poliLinks"
x1_values = []
x2_values = []
y1_values = []
y2_values = []

with open(pathMeshLink, 'r') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=' ')

    for row in csv_reader:
        x1_values.append(float(row[0]))
        y1_values.append(float(row[1]))
        x2_values.append(float(row[2]))
        y2_values.append(float(row[3]))

directorio_principal = '../'
elementos = os.listdir(directorio_principal)
carpetas_numericas = [elemento
                      for elemento
                      in elementos
                      if os.path.isdir(os.path.join(directorio_principal,
                                                    elemento))
                      and elemento.isdigit()]
carpetas_numericas_ordenadas = sorted(carpetas_numericas, key=int)
width = 12
height = 5
fig, ax = plt.subplots(1, 1, figsize=(width, height))
i_inicial = int(carpetas_numericas_ordenadas[0])


def actualizar(i):
    """Loop each timestep."""
    ax.clear()
    i = i_inicial + i
    print(i)
    fileName = directorio_principal + str(i) + "/xy"
    fileName2 = directorio_principal + str(i) + "/U"
    x_values = []
    y_values = []
    magnitud = []

    with open(fileName, 'r') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=' ')
        for row in csv_reader:
            x_values.append(float(row[0]))
            y_values.append(float(row[1]))

    with open(fileName2, 'r') as csv_file2:
        csv_reader = csv.reader(csv_file2, delimiter=' ')
        for row in csv_reader:
            magnitud.append(float(row[0]))

    ax.plot([x1_values, x2_values], [y1_values, y2_values], c="k", lw=1)
    vmin, vmax = 0.0, 1.3
    scatter = ax.scatter(x_values, y_values, c=magnitud,
                         cmap="jet_r", marker='o', edgecolors="none",
                         vmin=vmin, vmax=vmax)
    # text_esquina = "t = " + str(i) + "seg; evacuted: "
    # fig.text(0.05, 0.03, text_esquina, fontsize=12, fontweight='normal')
    ax.set_xlabel(
        't= {time} seg; evacuted:'.format(
            time=i))
    ax.xaxis.set_label_coords(0, -0.06)
    if i == i_inicial:
        cax = fig.add_axes([0.93, 0.1, 0.02, 0.8])
        plt.colorbar(scatter, cax=cax)
    # ax.set_axis_off()
    # if (i == "1"):
    #     xlim_auto = ax.get_xlim()
    #     ylim_auto = ax.get_ylim()
    # else:
    #     ax.set_xlim(xlim_auto)
    #     ax.set_ylim(ylim_auto)


ani = FuncAnimation(fig, actualizar, len(carpetas_numericas_ordenadas)-1,
                    interval=400, repeat_delay=900)
ani.save('animation.mp4')
