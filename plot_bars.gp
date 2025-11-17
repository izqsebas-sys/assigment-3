set title "Comparación de Movimientos Totales"
set xlabel "Algoritmo"
set ylabel "Distancia recorrida (cilindros)"
set style data histograms
set style fill solid 1.0 border -1
set grid ytics

plot "performance.dat" using 2:xtic(1) title "Head Movement"
