RAYOBJS = main1.o model.o camera.o list.o material.o plane.o \
object.o sphere.o image.o raytrace.o 

RAYHDRS = vector.h ray.h rayfuns.h rayhdrs.h

ray: $(RAYOBJS)
	gcc -Wall -o ray -g *.o -lm

$(RAYOBJS): $(RAYHDRS) makefile

.c.o: $<

	-gcc -c -Wall -c -g $< 2> $(@:.o=.err)
	cat $*.err
