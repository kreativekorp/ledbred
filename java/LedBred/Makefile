SRCFILES := $(shell find src -name \*.java)
PACKAGES := $(shell find src -name \*.java | sed -E s/^src\\/\|\\/[^\\/]+$$//g | grep -v \\.java$$ | sort | uniq | tr / .)

all: clean bin doc LEDBRED.JAR

eclipseall: eclipseclean LEDBRED.JAR

clean:
	rm -rf bin
	rm -rf doc
	rm -rf *.jar
	rm -rf *.JAR

eclipseclean:
	rm -rf *.jar
	rm -rf *.JAR

bin: src
	mkdir -p bin
ifeq ($(origin JAVACFLAGS), undefined)
	$(eval JAVACFLAGS = $(shell dep/minJavaVerOpts))
endif
	javac $(JAVACFLAGS) -sourcepath src $(SRCFILES) -d bin

doc: src
	mkdir -p doc
	javadoc $(JAVADOCFLAGS) -sourcepath src $(PACKAGES) -d doc

LEDBRED.JAR: bin
	export COPYFILE_DISABLE=true
	find bin -name .DS_Store -delete
	jar cmf dep/MANIFEST.MF LEDBRED.JAR -C bin com/kreative/ledbred
	chmod +x LEDBRED.JAR

.PHONY: all eclipseall clean eclipseclean
