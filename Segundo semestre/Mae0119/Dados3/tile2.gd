extends Panel

func _ready():
	pass
	
func set_color(r, g, b):
	get_node("Pipe").set_color(Color(r, g, b))
	
func set_colorc(color):
	get_node("Pipe").set_color(color)
	
func set_polygon(array):
	get_node("Pipe").set_polygon(array)