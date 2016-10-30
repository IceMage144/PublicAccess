
extends Node2D

const Tile = preload("res://tile.xscn")

const video_max_x = 1000
const video_max_y = 730
const graph_min_x = 1000
const graph_min_y = 530
const graph_max_x = 0
const graph_max_y = 0
const plot_min_x = 950
const plot_min_y = 50
const plot_max_x = 30
const plot_max_y = 500
const LightGray = Color(192, 192, 192)
const DarkGray = Color(64, 64, 64)
const Gray = Color(128, 128, 128)
const DarkBlue = Color(68, 68, 249)
const Black = Color(0, 0, 0)
const White = Color(255, 255, 255)
const Blue = Color(0, 0, 255)
const Red = Color(0, 100, 100)
const Orange = Color(255, 128, 0)
const Green = Color(0, 201, 87)
const Purple = Color(128, 0, 128)

var rand = 0
var maxplot = 10
var total = 1
var ocurr = [0, 0, 0, 0, 0, 0]
var Lines = [[], [], [], [], [], []]
var Aux = [0, 0]
var Colors = [Blue, Red, Orange, Green, Purple, Gray]

var board = [[], [], [], [], []]
var boardCorners = [Vector2(0, 0), Vector2(0, 315), Vector2(315, 315), Vector2(315, 0)]

func _ready():
#	get_node("Background").set_polygon(boardCorners)
#	get_node("Background").set_color(Color(0, 100, 100))
#	for i in range(5):
#		for j in range(5):
#			board[i].append(Tile.instance())
#			board[i][j].set_pos(Vector2(i*65, j*65))
#			board[i][j].set_polygon(boardCorners)
#			board[i][j].set_colorc(Colors[i])
#			add_child(board[i][j])
#	board[3][2].set_color(248, 255, 0)
	set_fixed_process(true)
	
func _fixed_process(delta):
#	var AuxVect = [Vector2(video_max_x, video_max_y), Vector2(0, 0), Vector2(0, video_max_y)]
#	board[0][0].set_polygon(AuxVect)
	update()
	
func _draw():
	draw_line(Vector2(0, 0), Vector2(200, 200), Blue, 10)
