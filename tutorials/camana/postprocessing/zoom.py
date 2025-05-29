"""Figure each timestep."""
import csv
import matplotlib.pyplot as plt
import os
import progressbar
from screeninfo import get_monitors
from mpl_toolkits.axes_grid1.inset_locator import zoomed_inset_axes as zoom_inset_axes
from os import path

#files
ruta_absoluta = path.abspath(__file__)
directory_main = path.dirname(path.dirname(ruta_absoluta))
directory_data = path.join(directory_main, "data/")
directory_export = path.join(directory_main, "postprocessing/snapshot/")
os.makedirs(directory_export, exist_ok=True)
directory_mesh = path.join(directory_main, "mesh/poliLinks")

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

bar = progressbar.ProgressBar(maxval=len(carpetas_numericas_ordenadas)).start()
screen_width = get_monitors()[0].width
screen_height = get_monitors()[0].height
width = screen_width/100
height = screen_height/100

for i in carpetas_numericas_ordenadas:
    fileName = directory_data + i + "/xy"
    fileName2 = directory_data + i + "/U"
    fileName3 = directory_data + i + "/cantPedestrianEvacuated"
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
    # figura
    fig, ax = plt.subplots(1, 1, figsize=(width, height))
    fig.subplots_adjust(left=0.05, right=0.95, top=0.98, bottom=0.03, wspace=0.3, hspace=0.09)
    # linea y puntos
    ax.plot([x1_values, x2_values], [y1_values, y2_values], c="k", lw=0.5)
    vmin, vmax = 0.0, 1.3
    # puntos o personas
    scatter = ax.scatter(x_values, y_values, c=magnitud,s=8,
                         cmap="jet_r", marker='o', edgecolors="none",
                         vmin=vmin, vmax=vmax)
    # zoom
    axins = zoom_inset_axes(ax, zoom=5, loc='upper right')
    axins.plot([x1_values, x2_values], [y1_values, y2_values], c="k", lw=1)
    axins.scatter(x_values, y_values, c=magnitud,
                  cmap="jet_r", marker='o', edgecolors="none",
                  vmin=vmin, vmax=vmax)
    # texto
    cantPeEv = str(int(cantPedestrianEvacuated[0]))
    text1 = "t = " + i + " seg; evacuated: " + cantPeEv
    fig.text(0.05, 0.03, text1, fontsize=12, fontweight='normal',
             transform=ax.transAxes)
    plt.colorbar(scatter, ax=ax, fraction=0.04)
    # configuraciones
    xlim_auto = ax.get_xlim()
    ylim_auto = ax.get_ylim()
    ax.set_xlim(xlim_auto)
    ax.set_ylim(ylim_auto)
    axins.set_xlim({746500, 747500})
    axins.set_ylim({8157400, 8158000})
    plt.xlabel('Valores X')
    plt.ylabel('Valores Y')
    plt.savefig(directory_export + i)
    plt.close(fig)
    bar.update(carpetas_numericas_ordenadas.index(i) + 1)
bar.finish()
