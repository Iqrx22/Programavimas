import pygame, os, random


WIDTH, HEIGHT = 1920, 960
WIN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Snake!")

DARK_BLUE = (0, 0, 50)
WHITE = (255, 255, 255)

FPS = 2

BACKROUND_IMAGE = pygame.image.load(os.path.join('Assets', 'grid.png'))
APPLE_IMAGE = pygame.image.load(os.path.join('Assets', 'apple.png'))
SNAKE_BODY_IMAGE = pygame.image.load(os.path.join('Assets', 'snake_body.png'))
SNAKE_HEAD_IMAGE = pygame.image.load(os.path.join('Assets', 'snake_head.png'))
SNAKE_CORNER_IMAGE = pygame.image.load(os.path.join('Assets', 'snake_corner.png'))
SNAKE_TAIL_IMAGE = pygame.image.load(os.path.join('Assets', 'snake_tail.png'))

BOARD_WIDTH, BOARD_HEIGHT = 30, 15

NIEKO = 0
SNAKE_HEAD = 1
SNAKE_BODY = 2
SNAKE_TAIL = 3
APPLE = 4

RETURN_RUN_GAME = 0
RETURN_RUN_GAME_APPLE = 1
RETURN_START_SCREEN = 2
RETURN_END_BORDER = 3
RETURN_END_CRASH = 4

BOARD_PIXELS = 64

pygame.font.init()
you_lost_font = pygame.font.SysFont('Comic Sans MS', HEIGHT//3)
apple_counter_font = pygame.font.SysFont('Comic Sans MS', 40)

def create_board(Board, Snake):
    for x in range(BOARD_HEIGHT):
        laikinas = []
        for y in range(BOARD_WIDTH):
            laikinas.insert(0, 0)

        Board.insert(0, laikinas)
    Snake.insert(0, [7, 2])
    for i in range(3, 5):
        Board[7][i] = SNAKE_BODY
        Snake.insert(0, [7, i])
    Board[7][2] = SNAKE_TAIL
    Board[7][5] = SNAKE_HEAD
    Snake.insert(0, [7, 5])

def generate_apple(Board):
    run = True
    while run:
        ran_x = random.randint(0, BOARD_HEIGHT-1)
        ran_y = random.randint(0, BOARD_WIDTH-1)
        #print(ran_x, ran_y, sep = ", ")

        if Board[ran_x][ran_y] == NIEKO:
            Board[ran_x][ran_y] = APPLE
            run = False

def change_snake(Board, Snake, Snake_direction, how_many_apples):
    Board[Snake[0][0]][Snake[0][1]] = SNAKE_BODY #pakeicia galva i kuna

    if Snake_direction == 0: #prideda snako galva i ta puse
        Snake.insert(0, [Snake[0][0]-1, Snake[0][1]])
    if Snake_direction == 1:
         Snake.insert(0, [Snake[0][0], Snake[0][1]+1])
    if Snake_direction == 2:
       Snake.insert(0, [Snake[0][0]+1, Snake[0][1]])
    if Snake_direction == 3:
         Snake.insert(0, [Snake[0][0], Snake[0][1]-1])

    snake_last = len(Snake)-1 #sukuria kintamaji, rodanti i paskutini snake elementa

    if ((Snake[0][0] == -1 or Snake[0][0] == BOARD_HEIGHT) or (Snake[0][1] == -1 or Snake[0][1] == BOARD_WIDTH)):
        return RETURN_END_BORDER
    elif Board[Snake[0][0]][Snake[0][1]] == SNAKE_BODY or Board[Snake[0][0]][Snake[0][1]] == SNAKE_TAIL:
        return RETURN_END_CRASH

    ka_returnint = 0

    if Board[Snake[0][0]][Snake[0][1]] != APPLE: #jeigu ten, kur turi buti snakas, yra obuolys, neistrinti uodegos
         Board[Snake[snake_last-1][0]][Snake[snake_last-1][1]] = SNAKE_TAIL #pakeicia priespaskutini elementa i uodega
         Board[Snake[snake_last][0]][Snake[snake_last][1]] = NIEKO #istrina gyvates uodega is boardo
         Snake.pop(snake_last) #istrina gyvates uodega is snako
    else:
        how_many_apples += 1
        generate_apple(Board)
        ka_returnint = 1

    Board[Snake[0][0]][Snake[0][1]] = SNAKE_HEAD #ideda galva
    return ka_returnint
    
def update_display(Board, started, how_many_apples):
    WIN.fill(DARK_BLUE)
    if started == 0:
        WIN.blit(BACKROUND_IMAGE, (0, 0))
        apple_counter = apple_counter_font.render(str(how_many_apples), False, WHITE)
        WIN.blit(apple_counter, (0, 0))
        for x in range(0, BOARD_HEIGHT):
            for y in range(BOARD_WIDTH):
                 if Board[x][y] == APPLE:
                      WIN.blit(APPLE_IMAGE, (y*BOARD_PIXELS, x*BOARD_PIXELS))
                 if Board[x][y] == SNAKE_BODY:
                     WIN.blit(SNAKE_BODY_IMAGE, (y*BOARD_PIXELS, x*BOARD_PIXELS))
                 if Board[x][y] == SNAKE_HEAD:
                     WIN.blit(SNAKE_HEAD_IMAGE, (y*BOARD_PIXELS, x*BOARD_PIXELS))
                 if Board[x][y] == SNAKE_TAIL:
                     WIN.blit(SNAKE_TAIL_IMAGE, (y*BOARD_PIXELS, x*BOARD_PIXELS))
    if started == 2:
        text_surface = you_lost_font.render('You Lost', False, WHITE)
        WIN.blit(text_surface, (0, 0))
   
    if started == 1:
        text_surface = you_lost_font.render('To start the game,\n press ENTER', False, WHITE)
        WIN.blit(text_surface, (0, 0))
    pygame.display.update()

def snakegame():
    Board = []
    Snake = []
    Snake_direction = 1
    how_many_apples = 0

    create_board(Board, Snake)
    generate_apple(Board)

    ar_game_vyksta = RETURN_RUN_GAME

    clock = pygame.time.Clock()
    run = True
    while run:
        clock.tick(FPS)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    ar_game_vyksta = 4
                if ar_game_vyksta == RETURN_RUN_GAME:
                    if event.key == pygame.K_LEFT:
                        if Snake_direction != 1 and Snake_direction != 3:
                            Snake_direction = 3
                            break
                    if event.key == pygame.K_RIGHT: 
                        if Snake_direction != 3 and Snake_direction != 1:
                            Snake_direction = 1
                            break
                    if event.key == pygame.K_UP:
                        if Snake_direction != 2 and Snake_direction != 0:
                             Snake_direction = 0
                             break
                    if event.key == pygame.K_DOWN:
                        if Snake_direction != 0 and Snake_direction != 2:
                            Snake_direction = 2
                            break

        
        if ar_game_vyksta == RETURN_RUN_GAME:
            ar_game_vyksta = change_snake(Board, Snake, Snake_direction, how_many_apples)
            if ar_game_vyksta == RETURN_RUN_GAME_APPLE:
                how_many_apples += 1
                ar_game_vyksta = RETURN_RUN_GAME
    
        update_display(Board, ar_game_vyksta, how_many_apples)

    pygame.quit()

if __name__ == "__main__":
    snakegame()
