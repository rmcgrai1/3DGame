#include<iostream>
#include <iomanip>
#include <vector>

#include "PosSpec.h"
using namespace std;
PosSpec::PosSpec(int NEWleftx, int NEWtopy, int NEWwidth, int NEWheight) {
	leftx = NEWleftx;
	topy = NEWtopy;
	width = NEWwidth;
	height = NEWheight;
	updatecalcs();
}

PosSpec::PosSpec(const PosSpec &needscopied) {
	leftx = needscopied.leftx;
	topy = needscopied.topy;
	width = needscopied.width;
	height = needscopied.height;
	updatecalcs();
}

PosSpec *PosSpec::InsetFraction(double xFrac, double yFrac) {
	PosSpec *output = new PosSpec(*this);
	output->InsetByFraction(xFrac,yFrac);
	return output;
}

PosSpec *PosSpec::ScaleFraction(double xFrac, double yFrac) {
	PosSpec *output = new PosSpec(*this);
	output->ScaleByFraction(xFrac,yFrac);
	return output;
}

vector<PosSpec *> PosSpec::SplitUp(int xsplit, int ysplit) {
	vector<PosSpec *> output;
	if(!xsplit) {
		xsplit = 1;
	}
	if(!ysplit) {
		ysplit = 1;
	}
	double xFrac = 1/xsplit;
	double yFrac = 1/ysplit;
	int newWidth = width/xsplit;
	int newHeight = height/ysplit;
	int i,j;
	for(i=0;i<xsplit;i++) {
		for(j=0;j<ysplit;j++) {
			output.push_back(ScaleFraction(xFrac,yFrac));
			output.back()->setTopLeft(leftx+newWidth*i,topy+newHeight*j);
		}
	}
	return output;
}

void PosSpec::UpdateSplit(int xsplit, int ysplit, vector<PosSpec *> *List) {
	if(!xsplit) {
		xsplit = 1;
	}
	if(!ysplit) {
		ysplit = 1;
	}
	double xFrac = 1./xsplit;
	double yFrac = 1./ysplit;
	int newWidth = width/xsplit;
	int newHeight = height/ysplit;
	while(List->size()) {
		List->pop_back();
	}
	int i,j;
	for(i=0;i<xsplit;i++) {
		for(j=0;j<ysplit;j++) {
			List->push_back(ScaleFraction(xFrac,yFrac));
			List->back()->setTopLeft(leftx+newWidth*i,topy+newHeight*j);
		}
	}
}

PosSpec *PosSpec::InsetAmount(int xIns, int yIns) {
	PosSpec *output = new PosSpec(*this);
	output->InsetByAmount(xIns, yIns);
	return output;
}

void PosSpec::InsetByFraction(double xFrac, double yFrac) {
	scaleCenter(1-2*xFrac,1-2*yFrac);
}

void PosSpec::ScaleByFraction(double xFrac, double yFrac) {
	scaleCenter(xFrac,yFrac);
}

void PosSpec::InsetByAmount(int xIns, int yIns) {
	addDimCenter(-2*xIns, -2*yIns);
}

void PosSpec::InsetCopyByFraction(double xFrac, double yFrac, PosSpec *output) {
	*output = *this;
	output->InsetByFraction(xFrac,yFrac);
}

void PosSpec::ScaleCopyByFraction(double xFrac, double yFrac, PosSpec *output) {
	*output = *this;
	output->ScaleByFraction(xFrac,yFrac);
}

void PosSpec::InsetCopyByAmount(int xIns, int yIns, PosSpec *output) {
	*output = *this;
	output->InsetByAmount(xIns, yIns);
}

int PosSpec::isInside(int x, int y) {
	if((leftx<=x && x<=rightx) || (rightx<=x && x<=leftx)) {
		if((topy<=y && y<=bottomy) || (bottomy<=y && y<=topy)) {
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

void PosSpec::setTopLeft(int x, int y) {
	leftx = x;
	topy = y;
	updatecalcs();
}

void PosSpec::setTopLeftStretch(int x, int y) {
	leftx = x;
	topy = y;
	width = rightx - leftx;
	height = bottomy - topy;
	updatecalcs();
}

void PosSpec::setBottomRight(int x, int y) {
	width = x - leftx;
	height = y - topy;
	updatecalcs();
}

void PosSpec::setBottomRightMove(int x, int y) {
	leftx += x-rightx;
	topy += y-bottomy;
	updatecalcs();
}

void PosSpec::scale(double xS, double yS) {
	width*=xS;
	height*=yS;
	updatecalcs();
}

void PosSpec::scale(double s) {
	scale(s,s);
}

void PosSpec::scaleCenter(double xS, double yS) {
	int prevXC = centerx;
	int prevYC = centery;
	scale(xS,yS);
	setCenter(prevXC, prevYC);
}

void PosSpec::scaleCenter(double s) {
	scaleCenter(s,s);
}

void PosSpec::setCenter(int x, int y) {
	leftx += x-centerx;
	topy += y-centery;
	updatecalcs();
}

void PosSpec::setCenterScaleTL(int x, int y) {
	//xScale = (x-leftx) / (centerx - leftx)
	//xScale = (x-leftx) / (width / 2)
	double xScale = (2*(x-leftx)) / ((double)width);
	double yScale = (2*(y-topy)) / ((double)height);
	scale(xScale,yScale);
	if((centerx != x) | (centery != y)) {
		cout << "WARNING: Scale by center (TL) was incorrect!\n";
		cout << "Center of [" << *this << "] should be (" << x << "," << y << "), but is (" << centerx << "," << centery << ")\n";
	}
}

void PosSpec::setCenterScaleBR(int x, int y) {
	int prevXright = rightx;
	int prevYbottom = bottomy;
	//xScale = (rightx-x) / (rightx - centerx)
	//xScale = (rightx-x) / (width / 2)
	double xScale = (2*(rightx-x)) / ((double)width);
	double yScale = (2*(bottomy-y)) / ((double)height);
	scale(xScale,yScale);
	setBottomRightMove(prevXright, prevYbottom);
	if((centerx != x) | (centery != y)) {
		cout << "WARNING: Scale by center (BR) was incorrect!\n";
		cout << "Center of [" << *this << "] should be (" << x << "," << y << "), but is (" << centerx << "," << centery << ")\n";
	}
}

void PosSpec::setWidth(int NewWidth) {
	width = NewWidth;
	updatecalcs();
}

void PosSpec::setHeight(int NewHeight) {
	height = NewHeight;
	updatecalcs();
}

void PosSpec::changeDim(int NewWidth, int NewHeight) {
	width = NewWidth;
	height = NewHeight;
	updatecalcs();
}

void PosSpec::changeDimCenter(int NewWidth, int NewHeight) {
	int prevXC = centerx;
	int prevYC = centery;
	changeDim(NewWidth,NewHeight);
	setCenter(prevXC, prevYC);
}

void PosSpec::addDim(int x, int y) {
	changeDim(width + x, height + y);
}

void PosSpec::addDimCenter(int x, int y) {
	changeDimCenter(width + x, height + y);
}

int PosSpec::getWidth() {
	return width;
}

int PosSpec::getHeight() {
	return height;
}

int PosSpec::getLeftX() {
	return leftx;
}

int PosSpec::getTopY() {
	return topy;
}

int PosSpec::getRightX() {
	return rightx;
}

int PosSpec::getBottomY() {
	return bottomy;
}

int PosSpec::getCenterX() {
	return centerx;
}

int PosSpec::getCenterY() {
	return centery;
}

void PosSpec::updatecalcs() {
	rightx = leftx + width;
	bottomy = topy + height;
	centerx = leftx + width/2;
	centery = topy + height/2;
}

ostream& operator<<(ostream& output, const PosSpec spec) {
	output << "topleft:(" << spec.leftx << "," << spec.topy << "), dimensions:(" << spec.width << "," << spec.height << ")";
	return output;
}