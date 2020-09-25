SHELL   = /bin/bash
BASEDIR = '/cvolume'

make_env:
	mkdir -p $(HOME)$(BASEDIR)/{R,G,B,Not_trusted,temp}
# Getting the config file
ifeq (,$(wildcard ./configuracion.config))
	wget https://raw.githubusercontent.com/kisung5/Tarea1SOs/master/server-c/configuracion.config
endif
# This is to build the project image, not needed really	
#	sudo docker build -t centos-server .
# This is for running directly the server

run:
	sudo docker run -p 9090:9090 -it -v $(HOME)$(BASEDIR):/volume --env-file configuracion.config  ksnonsteal/centos-imagecserver

rmvolume:
	sudo rm -r $(HOME)/cvolume

clean:
	sudo rm -r $(HOME)/cvolume
	sudo rm configuracion.config