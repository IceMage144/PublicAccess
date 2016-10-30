extends Control


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
const Gray = Color(128, 128, 128)
const DarkBlue = Color(68, 68, 249)
const Black = Color(0, 0, 0)
const White = Color(255, 255, 255)
const Blue = Color(0, 0, 255)
const Red = Color(220, 20, 60)
const Orange = Color(255, 128, 0)
const Green = Color(0, 201, 87)
const Purple = Color(128, 0, 128)

var ready = 0
var rand = 0
var maxplot = 100
var total = 1
var ocurr = [0, 0, 0, 0, 0, 0]
var Lines = [[], [], [], [], [], []]
var Aux = [Vector2(plot_min_x, plot_max_y), Vector2(plot_min_x, plot_max_y), Vector2(plot_min_x, plot_max_y), Vector2(plot_min_x, plot_max_y), Vector2(plot_min_x, plot_max_y), Vector2(plot_min_x, plot_max_y)]

func _ready():
	set_fixed_process(true)
	set_process_input(true)
	
func _fixed_process(delta):
	if (int(get_node("LineEdit").get_text()) != 0 and Input.is_action_pressed("enter_string")):
		maxplot = int(get_node("LineEdit").get_text())
		ocurr = [0, 0, 0, 0, 0, 0]
		Lines = [[], [], [], [], [], []]
		total = 1
		Aux = [Vector2(plot_min_x, plot_max_y), Vector2(plot_min_x, plot_max_y), Vector2(plot_min_x, plot_max_y), Vector2(plot_min_x, plot_max_y), Vector2(plot_min_x, plot_max_y), Vector2(plot_min_x, plot_max_y)]
		get_node("LineEdit").clear()
		ready = 1
	elif (Input.is_action_pressed("enter_string")):
		get_node("LineEdit").clear()
	for i in range(maxplot):
		if (total < maxplot && maxplot != 0):
			rand = randi()%6
			ocurr[rand] += 1
			for i in range(6):
				Lines[i].append([Vector2(plot_min_x+(plot_max_x-plot_min_x)*total/maxplot, plot_max_y-(plot_max_y-plot_min_y)*ocurr[i]/total), Aux[i]])
				Aux[i] = Lines[i][total-1][0]
			total += 1
	if (ready == 1):
		get_node("Graph").draw_graph(Lines, total, maxplot)
		ready = 0
	pass

func _on_Button_pressed():
	if (int(get_node("LineEdit").get_text()) != 0):
		maxplot = int(get_node("LineEdit").get_text())
		ocurr = [0, 0, 0, 0, 0, 0]
		Lines = [[], [], [], [], [], []]
		total = 1
		Aux = [Vector2(plot_min_x, plot_max_y), Vector2(plot_min_x, plot_max_y), Vector2(plot_min_x, plot_max_y), Vector2(plot_min_x, plot_max_y), Vector2(plot_min_x, plot_max_y), Vector2(plot_min_x, plot_max_y)]
		get_node("LineEdit").clear()
		ready = 1
	else:
		get_node("LineEdit").clear()