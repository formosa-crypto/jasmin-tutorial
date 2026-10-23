SUBDIRS = spill optimization sort

.PHONY: all run clean

all run clean:
	@for d in $(SUBDIRS); do $(MAKE) -C $$d $@ || exit 1; done
