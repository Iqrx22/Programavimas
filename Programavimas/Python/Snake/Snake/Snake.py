import pygame

WIDTH, HEIGHT = 1920, 1017
WIN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Snake!")

DARK_BLUE = (0, 0, 30)

def main():
    
    run = True;
    while run:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run == False

        WIN.fill(DARK_BLUE)
        pygame.display.update()

    pygame.quit()

if __name__ == "__main__":
    main()
