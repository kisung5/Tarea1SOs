FROM centos
WORKDIR /server-c
RUN dnf install -y epel-release
RUN yes | yum install dnf-plugins-core
RUN dnf config-manager --set-enabled PowerTools
RUN dnf install -y ImageMagick ImageMagick-devel 
COPY main.c main.out ./
CMD [ "./main.out" ]