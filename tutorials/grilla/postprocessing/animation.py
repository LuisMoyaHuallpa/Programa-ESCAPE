"""Figure each timestep."""
import csv
import matplotlib.pyplot as plt
import os
from matplotlib.animation import FuncAnimation
from screeninfo import get_monitors
from progressbar import ProgressBar
from os import path

#files
ruta_absoluta = path.abspath(__file__)
directory_main = path.dirname(path.dirname(ruta_absoluta))
directory_mesh = path.join(directory_main, "mesh/poliLinks")
directory_data = path.join(directory_main, "data/")
directory_export = path.join(directory_main, "postprocessing/snapshot/")

x1_values = []
x2_values = []
y1_values = []
y2_values = []

with open(directory_mesh, 'r') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=' ')

    for row in csv_reader:
        x1_values.append(float(row[0]))
        y1_values.append(float(row[1]))
        x2_values.append(float(row[2]))
        y2_values.append(float(row[3]))

elementos = os.listdir(directory_data)
carpetas_numericas = [elemento
                      for elemento
                      in elementos
                      if os.path.isdir(os.path.join(directory_data,
                                                    elemento))
                      and elemento.isdigit()]
carpetas_numericas_ordenadas = sorted(carpetas_numericas, key=int)
bar = ProgressBar(maxval=len(carpetas_numericas_ordenadas)).start()

width = 12
height = 5
# tamaño de figura
screen_width = get_monitors()[0].width
screen_height = get_monitors()[0].height
width = screen_width/100
height = screen_height/100

fig, ax = plt.subplots(1, 1, figsize=(width, height), tight_layout=True)
i_inicial = int(carpetas_numericas_ordenadas[0])


def actualizar(i):
    """Loop each timestep."""
    ax.clear()
    fileName = directory_data + carpetas_numericas_ordenadas[i] + "/xy"
    fileName2 = directory_data + carpetas_numericas_ordenadas[i] + "/U"
    fileName3 = directory_data + carpetas_numericas_ordenadas[i] + "/cantPedestrianEvacuated"
    x_values = []
    y_values = []
    magnitud = []
    cantPedestrianEvacuated = []

    with open(fileName, 'r') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=' ')
        for row in csv_reader:
            x_values.append(float(row[0]))
            y_values.append(float(row[1]))

    with open(fileName2, 'r') as csv_file2:
        csv_reader = csv.reader(csv_file2, delimiter=' ')
        for row in csv_reader:
            magnitud.append(float(row[0]))

    with open(fileName3, 'r') as csv_file3:
        csv_reader = csv.reader(csv_file3, delimiter=' ')
        for row in csv_reader:
            cantPedestrianEvacuated.append(float(row[0]))

    # lineas o calles
    ax.plot([x1_values, x2_values], [y1_values, y2_values], c="k", lw=1)
    vmin, vmax = 0.0, 1.3
    # puntos o personas
    scatter = ax.scatter(x_values, y_values, c=magnitud,
                         cmap="jet_r", marker='o', edgecolors="none",
                         vmin=vmin, vmax=vmax)
    # texto
    cantPeEv = str(int(cantPedestrianEvacuated[0]))
    text1 = "t = " + str(i) + " seg; evacuated: " + cantPeEv
    ax.text(0.05, 0.02, text1, fontsize=20, fontweight='normal',
            transform=ax.transAxes)
    # configuraciones
    ax.axis('off')
    # ax.xaxis.set_label_coords(0, -0.06)
    # ax.set_axis_off()
    if i == i_inicial:
        # cax = fig.add_axes([0.93, 0.1, 0.02, 0.8])
        plt.colorbar(scatter, ax=ax, fraction=0.03)
    # ax.set_axis_off()
    # if (i == "1"):
    #     xlim_auto = ax.get_xlim()
    #     ylim_auto = ax.get_ylim()
    # else:
    #     ax.set_xlim(xlim_auto)
    #     ax.set_ylim(ylim_auto)
    bar.update(i + 1)


ani = FuncAnimation(fig, actualizar, len(carpetas_numericas_ordenadas)-1,
                    interval=100, repeat_delay=900)
ani.save(directory_export + 'animation.mp4')
bar.finish()
