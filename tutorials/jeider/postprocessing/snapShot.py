"""Figure each timestep."""
import csv
import matplotlib.pyplot as plt
import os
import progressbar
from screeninfo import get_monitors

pathMeshLink = "../mesh/poliLinks"
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

bar = progressbar.ProgressBar(maxval=len(carpetas_numericas_ordenadas)).start()
screen_width = get_monitors()[0].width
screen_height = get_monitors()[0].height
width = screen_width/100
height = screen_height/100

for i in carpetas_numericas_ordenadas:
    fileName = directorio_principal + i + "/xy"
    fileName2 = directorio_principal + i + "/U"
    fileName3 = directorio_principal + i + "/cantPedestrianEvacuated"
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

    fig, ax = plt.subplots(1, 1, figsize=(width, height))
    ax.plot([x1_values, x2_values], [y1_values, y2_values], c="k", lw=1)
    vmin, vmax = 0.0, 1.3  # Ajusta los límites según tus necesidades
    scatter = ax.scatter(x_values, y_values, c=magnitud,
                         cmap="jet_r", marker='o', edgecolors="none",
                         vmin=vmin, vmax=vmax)
    # plt.title('Gráfico desde archivo CSV')
    plt.xlabel('Valores X')
    plt.ylabel('Valores Y')
    cantPeEv = str(int(cantPedestrianEvacuated[0]))
    text1 = "t = " + i + " seg; evacuated: " + cantPeEv
    fig.text(0.05, 0.03, text1, fontsize=12, fontweight='normal')
    plt.colorbar(scatter, ax=ax)
    # Ajusta los valores vmin y vmax según tus preferencias

    ax.set_axis_off()
    if (i == "1"):
        xlim_auto = ax.get_xlim()
        ylim_auto = ax.get_ylim()

    else:
        ax.set_xlim(xlim_auto)
        ax.set_ylim(ylim_auto)

    plt.savefig("snapShot/" + i)
    plt.close(fig)
    bar.update(carpetas_numericas_ordenadas.index(i) + 1)
bar.finish()
