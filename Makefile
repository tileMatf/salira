
all:
	cd src; make


clean:
	cd src; make clean

DEM=\
 demos/ansi.gs     demos/expr.gs     demos/match.gs    demos/squigol.gs\
 demos/arrayEx.gs  demos/fastsort.gs demos/matrix.gs   demos/stack.gs\
 demos/cat.gs      demos/iosynch.gs  demos/minsrand.gs demos/temps.gs\
 demos/evalred.gs  demos/lattice.gs  demos/queens.gs   demos/tree.gs\
 demos/examples.gs demos/lucqs.gs    demos/random.gs



PRE = cc.prelude         nofloat.prelude\
 standard.prelude   min.prelude    simple.prelude

BINDIR=/opt/gofer/bin
LIBDIR=/opt/gofer/lib

##The Docs say src/runtime.o is installed so in it goes!

install:
	@echo "Installing EXEC files ...."
	if [ -d $(BINDIR) ]; then set +x; \
	else (set -x; mkdirhier $(BINDIR)); fi
	bsdinst -c -s src/gofer $(BINDIR)
	bsdinst -c -s src/gofc $(BINDIR)
	bsdinst -c -s src/runtime.o $(BINDIR)
	for i in $(PRE) ; do \
		bsdinst -c -m 0644 $$i $(BINDIR) ; \
	done
	bsdinst -c -m 0644 scripts/gofer $(BINDIR)
	bsdinst -c -m 0644 scripts/goferc $(BINDIR)
	@echo "Installing scripts ...."
	if [ -d $(LIBDIR) ]; then set +x; \
	else (set -x; mkdirhier $(LIBDIR)); fi
	for i in $(PRED) ; do \
		bsdinst -c -m 0644 $$i $(LIBDIR) ; \
	done
	for i in $(DEM) ; do \
		bsdinst -c -m 0644 $$i $(LIBDIR) ; \
	done

