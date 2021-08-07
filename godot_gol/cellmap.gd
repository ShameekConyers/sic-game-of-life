extends TileMap

const TILE_SIZE = 8


export(int) var WIDTH 
export(int) var HEIGHT
onready var cam = $Camera2D
onready var label = $Control/Label

var playing = false
var back_field
var counter = 0

func _ready() -> void:
	
	var width_px = WIDTH * TILE_SIZE
	var height_px = HEIGHT * TILE_SIZE
	cam.position = Vector2(width_px, height_px) / 2
	cam.zoom = Vector2(width_px, height_px) /  Vector2(1280, 800) 
	
	
	back_field = []
	for i in range(WIDTH):
		var back = []
		for j in range(HEIGHT):
			set_cell(i, j, 0)
			back.append(0)
		back_field.append(back)
		
func _input(event):
	if event.is_action_pressed("toggle_play"):
		playing = !playing
	if event.is_action_pressed("click"):
		var pos = (get_local_mouse_position()/TILE_SIZE).floor()
		set_cellv(pos, 1 - get_cellv(pos))
		
func _process(delta: float) -> void:
	if !playing:
		label.text = "PAUSED"
	else:
		label.text = ""
	if (counter % 10) == 0:
		update_field()
	counter += 1
	
func update_field():
	if !playing:
		return
	
	for i in range(WIDTH):
		for j in range(HEIGHT):
			var live_neighbors = 0
			for k in [-1, 0, 1]:
				for l in [-1, 0, 1]:
					if get_cell(i + k, j + l) == 1:
						live_neighbors += 1
			
			if get_cell(i, j) == 1:
				if live_neighbors in [3, 4]:
					back_field[i][j] = 1
				else:
					back_field[i][j] = 0
			else:
				if live_neighbors == 3:
					back_field[i][j] = 1
				else:
					back_field[i][j] = 0
			
			if randi() % 1000 == 2:
				back_field[i][j] = 1
			
			if randi() % 1000 == 3:
				back_field[i][j] = 0
				
	#...
	
	for i in range(WIDTH):
		for j in range(HEIGHT):
			set_cell(i, j, back_field[i][j])
						
