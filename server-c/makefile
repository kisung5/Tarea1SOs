
edit:
	mkdir -p $(HOME)/cvolume/{R,G,B,Not_trusted,temp}
# This is to build the project image, not needed really	
#	sudo docker build -t centos-server .
# This is for running directly the server
	sudo docker run -p 9090:9090 -it -v $(HOME)/cvolume:/volume --env-file configuracion.config  centos-server

clean:
	sudo rm -r $(HOME)/cvolume