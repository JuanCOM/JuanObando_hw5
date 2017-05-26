Resultados_hw5.pdf : Resultados_hw5.tex RC.png canali.png 
	pdflatex Resultados_hw5.tex


RC.png : circuitoRC.py CircuitoRC.txt
	python $<

canali.png: plots_canal_ionico.py c.txt c1.txt
	python plots_canal_ionico.py
 
c.txt c1.txt : c_i Canal_ionico.txt Canal_ionico1.txt
	./a.out

c_i : canal_ionico.c
	cc canal_ionico.c -lm

