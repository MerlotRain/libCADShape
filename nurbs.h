/**
 * Copyright (c) 2023-present Merlot.Rain
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef NURBS_H
#define NURBS_H

#ifdef __cplusplus
"C" {
#endif

#include <stdint.h>

#define NURBS_TRUE              1
#define NURBS_FALSE             0

#define NURBS_GEOM_ARC          1
#define NURBS_GEOM_BEZIZER      2
#define NURBS_GEOM_CIRCLE       3
#define NURBS_GEOM_ELLIPSE      4
#define NURBS_GEOM_ELLIPSEARC   5
#define NURBS_GEOM_LINE         6

/* 
 Nurbs data
*/
typedef struct {
    double x;
    double y;
    double z;
} nurbs_Point;

typedef struct {
    double x;
    double y;
    double z;
} nurbs_Vector;

typedef struct {
    nurbs_Vector normal;
    nurbs_Point origin;
} nurbs_Plane;

typedef struct {
    nurbs_Vector dir;
    nurbs_Point origin;
} nurbs_Ray;

typedef struct {
    uint8_t degree;
    uint32_t ncv;
    uint32_t nknots;
    nurbs_Point* cv;
    double* knots;
} nurbs_CurveData;

typedef struct {
    uint8_t degreeU;
    uint8_t degreeV;
    uint32_t ncv;
    nurbs_Point* cv;
    double* knotsU;
    double* knotsV;
    uint32_t npointsU;
    uint32_t npointsV;
} nurbs_SurfaceData;


typedef struct {
    double u;
    double v;
} nurbs_UV;

typedef struct {
    double u;
    double len;
} nurbs_CurveSample;

/* Nurbs shapes */

#define GEOM_NURBS_DATA \
    int type;\
    nurbs_CurveData* nurbs_data;

typedef struct {
    GEOM_NURBS_DATA
} nurbs_Curve;

typedef struct {
    GEOM_NURBS_DATA

    nurbs_Point _point;
    nurbs_Vector _xaxis;
    nurbs_Vector _yaxis;
    double _radius;
    double _minAngle;
    double _maxAngle;
} nurbs_Arc, nurbs_Circle;

typedef struct {
    GEOM_NURBS_DATA
} nurbs_BezierCurve;

typedef struct {
    GEOM_NURBS_DATA

    nurbs_Point _point;
    nurbs_Vector _xaxis;
    nurbs_Vector _yaxis;
    double _minAngle;
    double _maxAngle; 
} nurbs_EllipseArc, nurbs_Ellipse;

typedef struct {
    GEOM_NURBS_DATA

    nurbs_Point _start;
    nurbs_Point _end;
} nurbs_Line;

void nurbs_free(nurbs_Curve* curve);

nurbs_Curve* nurbs_new_curve_withKCW(uint8_t degree, const nurbs_Point* cv, uint32_t ncv, double* knots, uint32_t nknots, double* weights, uint32_t nweights);

nurbs_Curve* nurbs_new_curve_withP(const nurbs_Point* cv, uint32_t ncv, uint8_t degree);

nurbs_Arc* nurbs_new_arc(const nurbs_Point center, const nurbs_Vector xaxis, const nurbs_Vector yaxis, double radius, double minAngle, double maxAngle);

nurbs_BezierCurve* nurbs_new_bezier(const nurbs_Point* points, uint32_t npoints, double* weights, int nw);

nurbs_Circle* nurbs_new_circle(const nurbs_Point center, const nurbs_Vector xaxis, const nurbs_Vector yaxis, double radius);

nurbs_EllipseArc* nurbs_new_ellipsearc(const nurbs_Point center, const nurbs_Vector xaxis, const nurbs_Vector yaxis, double minAngle, double maxAngle);

nurbs_Ellipse* nurbs_new_ellipse(const nurbs_Point center, const nurbs_Vector xaxis, const nurbs_Vector yaxis);

nurbs_Line* nurbs_new_line(const nurbs_Point start, const nurbs_Point end);

void nurbs_curve_reverse(nurbs_Curve* curve);

void nurbs_curve_domain(const nurbs_Curve* curve, double* min, double* max);

void nurbs_curve_transform(nurbs_Curve* curve, void* mat);

nurbs_Point nurbs_curve_point(const nurbs_Curve* curve, double u);

nurbs_Vector nurbs_curve_tangent(const nurbs_Curve* curve, double u);

int nurbs_curve_derivatives(const nurbs_Curve* curve, double u, int nderives, nurbs_Vector** v, int *nv);

nurbs_Point nurbs_curve_closepoint(const nurbs_Curve* curve, const nurbs_Point point);

double nurbs_curve_closeparam(const nurbs_Curve* curve, const nurbs_Point point);

double nurbs_curve_length(const nurbs_Curve* curve);

double nurbs_curve_lengthAtParam(const nurbs_Curve* curve, double u);

double nurbs_curve_paramAtLength(const nurbs_Curve* curve, double len);

int nurbs_curve_divideByEqualArcLength(const nurbs_Curve* curve, int divisions, nurbs_CurveSample** samples, int *ns);

int nurbs_curve_divideByArcLength(const nurbs_Curve* curve, double arclength, nurbs_CurveSample** samples, int *ns);

int nurbs_curve_split(const nurbs_Curve* curve, double u, nurbs_Curve** curves, int *nc);

int nurbs_curve_tessellate(const nurbs_Curve* curve, double tol, nurbs_Point** points, int *np);


#ifdef __cplusplus
}
#endif

#endif /* NURBS_H */