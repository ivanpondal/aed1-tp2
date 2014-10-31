define 2spec =
python2 ../tools/algo1converter.py pics/$(basename $@).png \\
			$(basename $@).specimg 0
python2 ../tools/algo1converter.py filtered/$(basename $@).acuarela.k5.png \\
			$(basename $@).acuarela.k5.specimg 0
python2 ../tools/algo1converter.py filtered/$(basename $@).blur.k5.png \\
		$(basename $@).blur.k5.specimg 0

endef


all: specimgs

clean:
	rm -f *.specimg

specimgs: hermione.specimg jennifer.specimg ACDC.specimg

hermione.specimg:
	$(2spec)

jennifer.specimg:
	$(2spec)

ACDC.specimg:
	$(2spec)
