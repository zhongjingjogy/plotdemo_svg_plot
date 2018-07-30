#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <boost/svg_plot/svg_2d_plot.hpp>

void deserialize(
    std::string src,
    std::vector<std::vector<double> > &var) {

    std::ifstream infile;
	infile.open(src.c_str(), std::ios::binary|std::ios::in);

    if(!infile.is_open()) {
        std::cout << "The file can not be open.\n";
    }
    while(infile.is_open() && !infile.eof()) {
        int size = 0;
        if(infile.eof()) {
            break;
        }
        infile.read(reinterpret_cast<char *>(&size), sizeof(size));
        
        if(infile.eof()) {
            // std::cout << "size: " << size << "\n";
            // std::cerr << "Broken cols files.\n";
            break;
        }
        if(size == 0) {
            // std::cout << "empty array to be read\n";
            continue;
        }
        std::vector<double> v(size);
        infile.read(reinterpret_cast<char *>(&v[0]), sizeof(double)*size);
        var.push_back(v);
        // std::cout << strtool::join(v, ", ") << "\n";
    }
	
    infile.close();
}

boost::svg::svg_color svg_colors[] = {
	boost::svg::svg_color(0xff, 0x00, 0x00),
	boost::svg::svg_color(0x00, 0x00, 0xff),
	boost::svg::svg_color(0x00, 0x00, 0x00),
	boost::svg::svg_color(0x00, 0x80, 0x00),
	boost::svg::svg_color(0xff, 0x00, 0xff),
	boost::svg::svg_color(0xdb, 0x70, 0x93),
	boost::svg::svg_color(0x94, 0x00, 0xd3),
	boost::svg::svg_color(0x00, 0xff, 0xff),
	boost::svg::svg_color(0x00, 0xff, 0x00),
	boost::svg::svg_color(0xff, 0x8c, 0x00),
	boost::svg::svg_color(0xa5, 0x2a, 0x2a),
	boost::svg::svg_color(0xff, 0x14, 0x93),
	boost::svg::svg_color(0x00, 0xbf, 0x19),
	boost::svg::svg_color(0xa0, 0x52, 0x2d),
	boost::svg::svg_color(0xfa, 0x80, 0x72),
	boost::svg::svg_color(0x80, 0x80, 0x80),
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

using namespace boost::svg;

void simulateandplot() {
  
    std::vector<std::vector<double> > var;
    deserialize("couple_simconc_distance.cols", var);

    std::vector<std::vector<double> > expvar;
    deserialize("couple_expconc_distance.cols", expvar);

    int n = var.size() / 2;
    int N = var[0].size();

    int expn = expvar.size() / 2;
    int expN = expvar[0].size();

    double v_min = 1.1;
    double v_max = -0.1;

    for(int i=0; i<n; i++) {
        double vmin = *std::min_element(var[2*i+1].begin(), var[2*i+1].end());
        double vmax = *std::max_element(var[2*i+1].begin(), var[2*i+1].end());
        if(vmin < v_min) {
            v_min = vmin;
        }
        if(vmax > v_max) {
            v_max = vmax;
        }
    }

    double delta = v_max - v_min;
    double x_min = var[0][0];
    double x_max = var[0][N-1];
    double x_delta = x_max - x_min;
    double y_delta = - (v_min - 0.1*delta) + v_max + 0.1*delta;

    svg_2d_plot my_plot;

    // Size/scale settings.
    my_plot.size(700, 500)
        .x_range(var[0][0], var[0][N-1])
        .y_range(v_min - 0.1*delta, v_max + 0.1*delta);

    // Text settings.
    my_plot.x_label("Distance / m")
        .y_label("Mole fraction / at.")
        .y_major_labels_side(-1)
        .y_major_grid_on(true);

    // Commands.
    my_plot.legend_on(true)
        .plot_window_on(true)
        .x_label_on(true)
        .y_label_on(true);

    // Color settings.
    my_plot.background_color(svg_color(67, 111, 69))
        .legend_background_color(svg_color(207, 202,167))
        .legend_border_color(svg_color(102, 102, 84))
        .plot_background_color(svg_color(136, 188, 126))
        .title_color(white)
        .y_major_grid_color(black);

    // X axis settings.
    my_plot.x_major_interval(x_delta / 8.0)
        .x_major_tick_length(14)
        .x_major_tick_width(1)
        .x_minor_tick_length(7)
        .x_minor_tick_width(1)
        .x_num_minor_ticks(3)

    // Y axis settings.
        .y_major_interval(y_delta / 8.0)
        .y_num_minor_ticks(5);

    // legend settings.
    my_plot.legend_title_font_size(15);

    for(int i=0; i<n; i++) {
        std::map<double, double> data;
        for(int nx=0; nx<N; nx++) {
            data[var[2*i][nx]] = var[2*i + 1][nx];
        }

        my_plot.plot(data, std::string("sim-") + std::to_string(i)).line_on(true).stroke_color(svg_colors[i]).shape(none).line_color(svg_colors[i]);
    }

    for(int i=0; i<expn; i++) {
        std::map<double, double> expdata;
        for(int nx=0; nx<expN; nx++) {
            expdata[expvar[2*i][nx]] = expvar[2*i + 1][nx];
        }

        my_plot.plot(expdata, std::string("exp-") + std::to_string(i)).shape(shapes[i]).stroke_color(svg_colors[i]);
    }
    my_plot.write("couple.svg");
}

int main(int argc, char *argv[])
{
	
    simulateandplot();
    return 0;
}