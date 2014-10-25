define 2spec =
python2 ../tools/algo1converter.py pics/$(basename $@).png $(basename $@).specimg 0
for m in acuarela blur; do \
	python2 ../tools/algo1converter.py filtered/$(basename $@).$$m.k5.png $(basename $@).$$m.k5.specimg 0; \
done
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
