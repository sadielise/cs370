JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
	BoundedBuffer.java \
	Consumer.java \
	Producer.java \
	Main.java 

default: classes

all: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class
