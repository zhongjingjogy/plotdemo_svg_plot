#include "serialize.hpp"
#include "svgplot_custom.hpp"

using namespace boost::svg;

void plotprofile() {
  
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
	
    plotprofile();
    return 0;
}