#ifndef POSSPEC_H
#define POSSPEC_H

#include<iostream>
#include <iomanip>
#include <vector>

using namespace std;
class PosSpec {
	friend ostream& operator<<(ostream&, const PosSpec);
	public:
		PosSpec(int NEWleftx = 0, int NEWtopy = 0, int NEWwidth = 10, int NEWheight = 10); // constructor
		PosSpec(const PosSpec &);
		PosSpec *InsetFraction(double xFrac, double yFrac);
		PosSpec *ScaleFraction(double xFrac, double yFrac);
		vector<PosSpec *> SplitUp(int xsplit, int ysplit);
		void UpdateSplit(int xsplit, int ysplit, vector<PosSpec *> *List);
		PosSpec *InsetAmount(int xIns, int yIns);
		void InsetByFraction(double xFrac, double yFrac);
		void ScaleByFraction(double xFrac, double yFrac);
		void InsetByAmount(int xIns, int yIns);
		void InsetCopyByFraction(double xFrac, double yFrac, PosSpec *output);
		void ScaleCopyByFraction(double xFrac, double yFrac, PosSpec *output);
		void InsetCopyByAmount(int xIns, int yIns, PosSpec *output);
		int isInside(int x, int y);
		void setTopLeft(int x, int y);
		void setTopLeftStretch(int x, int y);
		void setBottomRight(int x, int y);
		void setBottomRightMove(int x, int y);
		void scale(double xS, double yS);
		void scale(double s);
		void scaleCenter(double xS, double yS);
		void scaleCenter(double s);
		void setCenter(int x, int y);
		void setCenterScaleTL(int x, int y);
		void setCenterScaleBR(int x, int y);
		void setWidth(int NewWidth);
		void setHeight(int NewHeight);
		void changeDim(int NewWidth, int NewHeight);
		void changeDimCenter(int NewWidth, int NewHeight);
		void addDim(int x, int y);
		void addDimCenter(int x, int y);
		int getWidth();
		int getHeight();
		int getLeftX();
		int getTopY();
		int getRightX();
		int getBottomY();
		int getCenterX();
		int getCenterY();
		void updatecalcs();
	private:
		int leftx;
		int topy;
		int width;
		int height;
		
		// calculated variables:
		int rightx;
		int bottomy;
		int centerx;
		int centery;
};

#endif