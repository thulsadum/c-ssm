

all: ssm

.DEFAULT:
	(cd src; make $@)

clean:
	(cd src; make $@)
	(cd test; make $@)

.PHONY: test
test: compile
	(cd test; make $@)
