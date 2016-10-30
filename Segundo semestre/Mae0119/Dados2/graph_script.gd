extends Polygon2D

const video_max_x = 1000
const video_max_y = 730
const graph_min_x = 1000
const graph_min_y = 530
const graph_max_x = 0
const graph_max_y = 0
const plot_min_x = 40
const plot_min_y = 50
const plot_max_x = 960
const plot_max_y = 500
const LightGray = Color(192, 192, 192)
const DarkGray = Color(64, 64, 64)
const Green = Color(0, 255, 0)
const DarkBlue = Color(68, 68, 249)
const Black = Color(0, 0, 0)
const White = Color(255, 255, 255)
const Blue = Color(0, 0, 255)
const Red = Color(255, 0, 0)
const Orange = Color(255, 128, 0)
const Cyan = Color(0, 201, 87)
const Purple = Color(128, 0, 128)

var ready = 0
var Lines
var total
var Colors = [Blue, Red, Orange, Green, Purple, Cyan]
var maxplot
var triangle1 = [Vector2(plot_min_x, plot_min_y-5), Vector2(plot_min_x+5, plot_min_y+5), Vector2(plot_min_x-5, plot_min_y+5)]
var triangle2 = [Vector2(plot_max_x+5, plot_max_y), Vector2(plot_max_x-5, plot_max_y-5), Vector2(plot_max_x-5, plot_max_y+5)]
var triangleC = [Black, Black, Black]
var triangleUV = []

func draw_graph(MyLines, Mytotal, Mymaxplot):
	maxplot = Mymaxplot
	Lines = MyLines
	total = Mytotal
	ready = 1
	update()
	pass

func _draw():
	draw_line(Vector2(plot_min_x, plot_min_y), Vector2(plot_min_x, plot_max_y), Black, 1)
	draw_line(Vector2(plot_min_x, plot_max_y), Vector2(plot_max_x, plot_max_y), Black, 1)
	draw_line(Vector2(plot_min_x, plot_min_y+(plot_max_y-plot_min_y)*3/4), Vector2(plot_max_x, plot_min_y+(plot_max_y-plot_min_y)*3/4), Black, 1)
	draw_line(Vector2(plot_min_x, plot_min_y+(plot_max_y-plot_min_y)/2), Vector2(plot_max_x, plot_min_y+(plot_max_y-plot_min_y)/2), Black, 1)
	draw_line(Vector2(plot_min_x, plot_min_y+(plot_max_y-plot_min_y)/4), Vector2(plot_max_x, plot_min_y+(plot_max_y-plot_min_y)/4), Black, 1)
	draw_line(Vector2(plot_min_x, plot_min_y+(plot_max_y-plot_min_y)*5/6), Vector2(plot_max_x, plot_min_y+(plot_max_y-plot_min_y)*5/6), Black, 1)
	draw_primitive(triangle1, triangleC, triangleUV)
	draw_primitive(triangle2, triangleC, triangleUV)
	if (ready == 1):
		for i in range(6):
			for j in range(total-1):
				draw_line(Lines[i][j][0], Lines[i][j][1], Colors[i], 1)
		ready = 0
		