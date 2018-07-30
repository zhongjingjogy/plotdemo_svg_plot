#ifndef SVGPLOT_CUSTOM_HPP
#define SVGPLOT_CUSTOM_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <boost/svg_plot/svg_2d_plot.hpp>

boost::svg::svg_color svg_colors[] = {
    boost::svg::blueviolet,
    boost::svg::cadetblue,
    boost::svg::chocolate,
    boost::svg::cornflowerblue,
    boost::svg::darkcyan,
    boost::svg::deepskyblue,
    boost::svg::forestgreen,
    boost::svg::mediumseagreen,
    boost::svg::orchid,
    boost::svg::royalblue,
    boost::svg::teal,
    boost::svg::rosybrown,
    boost::svg::salmon,
    boost::svg::turquoise,
    boost::svg::yellowgreen
};

boost::svg::point_shape shapes[] = {
	boost::svg::circlet, /*!< Circle. Name was changed to round to avoid clash with function named circle,
	but was then found to clash with C++ Standard numeric function round.
	Full qualification `point_shape::round` requires C++11 support to compile, so then changed to circlet.
	*/
	boost::svg::square, //!< Square.
	// boost::svg::point, //!< Small solid point.
	// boost::svg::egg, //!< Ellipse.
	// boost::svg::unc_ellipse, //!< Ellipse sized using uncertainty estimate of x and y, typically about twice standard deviation or 95% confidence interval.
	boost::svg::vertical_line,  //!< Vertical line up & down from axis.
	// boost::svg::horizontal_line, //!< Horizontal line left & right from axis.
	// boost::svg::vertical_tick, //!< Vertical tick up from axis.
	// boost::svg::horizontal_tick, //!< Horizontal line right from axis.
	//!< Note horizontal will not be useful for 1D plot - will be on the axis.
	boost::svg::cone, //!< Cone pointing up - 'rightwayup'.
	boost::svg::triangle, //!< Triangle pointing down 'upsidedown'.
	boost::svg::star, //!< Star (using polygon).
	boost::svg::lozenge, //!< Lozenge or square with corners pointing up and down..
	boost::svg::diamond, //!< Diamond card shape.
	boost::svg::heart, //!< Heart playing card shape.
	boost::svg::club, //!< Club playing card shape.
	boost::svg::spade, //!< Spade playing card shape.
	boost::svg::asterisk, //!< Asterix as * symbol
	boost::svg::cross, //!< cross
};

#endif