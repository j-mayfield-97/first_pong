#pragma once
const int x = 450;
const int y = 450;

//this exist in this form because I wanted
//to make change the pointers of x and y to get a resizable window that scales.
//may be a better way to keep an enum

enum size
{
	screenHeight = y,
	screenWidth = x
};

