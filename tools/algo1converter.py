#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import numpy as np 
import cv2

""" 
Just need to install:

	sudo apt-get install python-numpy
	sudo apt-get install python-opencv

"""

def usage():
	print
	print "	usage: "
	print "		python algo1converter.py   in_file   out_file   method"
	print 
	print "	where method: "
	print " 		0:  	Image -> Spec 	"
	print " 		1: 	Spec  -> Image  "
	print

def showImg(imgname):
	img = cv2.imread(imgname,cv2.IMREAD_COLOR)		
	cv2.namedWindow('image', cv2.WINDOW_NORMAL)
	cv2.imshow('image',img)
	cv2.waitKey(0)
	cv2.destroyAllWindows()

def pic2spec():
	picname= str(sys.argv[1])
	outfile= str(sys.argv[2])

	img = cv2.imread(picname,cv2.IMREAD_COLOR)

	h,w= len(img),len(img[0])
	ps= []
	with open(outfile,'w') as f:
		for i in xrange(h):
			for j in xrange(w):
				ps.append(pixel2str(img,i,j))
		ss= str(h)+' '+str(w)+' ['+','.join(ps)+']\n'
		f.write(ss)
	# showImg(picname)

def spec2pic():
	picname= str(sys.argv[1])
	outfile= str(sys.argv[2])

	with open(picname,'r') as f:		
		data= f.readline().strip()
		h,w = map(int,data[0:data.find('[')].split())
		raw_img= data[data.find('[')+2:-2].split('),(')				
		img= blackBox(h,w)
		for i in xrange(h):
			for j in xrange(w):
				img[i][j]= map(int,raw_img[(i*w)+j].split(';'))

		# img= imgFilter(img,3)

		img= np.array(img)
		cv2.imwrite(outfile,img)

	# showImg(outfile)

def pixel2str(img,i,j):
	return '('+str(img[i][j][0])+';'+str(img[i][j][1])+';'+str(img[i][j][2])+')'

def kNeigh(img,k,x,y):
	pxs= []
	for i in xrange(x-k,x+k+1):
		for j in xrange(y-k,y+k+1):
			pxs.append(img[j][i])
	return pxs

def applyFilter(pxs,fx):
	prm= fx([px[0] for px in pxs])
	sgd= fx([px[1] for px in pxs])
	trc= fx([px[2] for px in pxs])
	return (prm,sgd,trc)

def pxBlack():
	return (0,0,0)

def blackBox(h,w):
	return [ [pxBlack()]*w for k in xrange(h) ]

def imgFilter(img,k):
	res= list(img)
	h,w= len(img),len(img[0])
	for x in xrange(w):
		for y in xrange(h):
			if x >= k and x < w-k and y >= k and y < h-k:

				""" blur """
				res[y][x]= applyFilter(kNeigh(img,k,x,y),np.mean)

				""" acuarela """
				# res[y][x]= applyFilter(kNeigh(img,k,x,y),np.median)
				
			else:
				res[y][x]= pxBlack()

	return res

if __name__ == '__main__':
	if len(sys.argv) != 4:
		usage()
		sys.exit()

	method= int(sys.argv[3])
	if method == 0:
		pic2spec()
	elif method == 1:
		spec2pic()
	else:
		print "Unknown method: ", method