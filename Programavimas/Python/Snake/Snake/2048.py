import pygame, os, random

WIDTH, HEIGHT = 600, 640
WIN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("2048!")

BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

BOARD_SIZE = 4

FPS = 5

GRID_IMAGE = pygame.image.load(os.path.join('Assets', 'grid.png'))

pygame.font.init()
status_font = pygame.font.SysFont('Comic Sans MS', 40)

def naujas_skaicius(lentele, didziausias):
    run = True
    while run:
        random_skaicius = random.randint(0, BOARD_SIZE**2-1)
        if lentele[random_skaicius//BOARD_SIZE][random_skaicius%BOARD_SIZE] == 0:
            random_skaicius2 = random.randint(0, 9)
            if random_skaicius2 == 0:
                lentele[random_skaicius//BOARD_SIZE][random_skaicius%BOARD_SIZE] = 4
                if didziausias < 4:
                    didziausias = 4
            else:
                lentele[random_skaicius//BOARD_SIZE][random_skaicius%BOARD_SIZE] = 2
                if didziausias < 2:
                    didziausias = 2
            run = False
    return didziausias


def sutraukti_i_puse(puse, lentele, didziausias):
    for kartotiketuris in range(0, 4):
        for eilute in range(0, BOARD_SIZE):
            for stulpelis in range(0, BOARD_SIZE):
                if puse == 3:
                    if lentele[eilute][stulpelis] == 0:
                        for stulpelis2 in range(stulpelis+1, 4):
                            if lentele[eilute][stulpelis2] != 0:
                                lentele[eilute][stulpelis] = lentele[eilute][stulpelis2]
                                lentele[eilute][stulpelis2] = 0
                                break
                    if lentele[eilute][stulpelis] == lentele[eilute][stulpelis+1]:
                        lentele[eilute][stulpelis] = 2*lentele[eilute][stulpelis]
                        if didziausias < lentele[eilute][stulpelis]:
                            didziausias = lentele[eilute][stulpelis]
                        lentele[eilute][stulpelis+1] = 0

                if puse == 1:
                    if lentele[eilute][3-stulpelis] == 0:
                        for stulpelis2 in range(2-stulpelis, -1):
                            if lentele[eilute][stulpelis2] != 0:
                                lentele[eilute][3-stulpelis] = lentele[eilute][stulpelis2]
                                lentele[eilute][stulpelis2] = 0
                                break
                if lentele[eilute][stulpelis] == lentele[eilute][stulpelis-1]:
                    lentele[eilute][stulpelis] = 2*lentele[eilute][stulpelis]
                    if didziausias < lentele[eilute][stulpelis]:
                            didziausias = lentele[eilute][stulpelis]
                    lentele[eilute][stulpelis-1] = 0

    for stulpelis in range(0, 4):
        for eilute in range(0, 4):
            if puse == 0:
                if lentele[eilute][stulpelis] == 0:
                    for eilute2 in range(eilute+1, 4):
                        if lentele[eilute2][stulpelis] != 0:
                            lentele[eilute][stulpelis] = lentele[eilute2][stulpelis]
                            lentele[eilute2][stulpelis] = 0
                            break
                if lentele[eilute][stulpelis] == lentele[eilute+1][stulpelis]:
                    lentele[eilute][stulpelis] = 2*lentele[eilute][stulpelis]
                    if didziausias < lentele[eilute][stulpelis]:
                            didziausias = lentele[eilute][stulpelis]
                    lentele[eilute+1][stulpelis] = 0

            if puse == 2:
                if lentele[3-eilute][stulpelis] == 0:
                    for eilute2 in range(2-eilute, 0):
                        if lentele[eilute2][stulpelis] != 0:
                            lentele[3-eilute][stulpelis] = lentele[eilute2][stulpelis]
                            lentele[eilute2][stulpelis] = 0
                            break
                if lentele[eilute][stulpelis] == lentele[eilute-1][stulpelis]:
                    lentele[eilute][stulpelis] = 2*lentele[eilute][stulpelis]
                    if didziausias < lentele[eilute][stulpelis]:
                            didziausias = lentele[eilute][stulpelis]
                    lentele[eilute-1][stulpelis] = 0
    return didziausias

def isvesti_busena(lentele, didziausias):
    WIN.fill(BLACK)
    WIN.blit(GRID_IMAGE, (0, 0))
    if didziausias <= 2048:
        text_surface = status_font.render('Your best score is: ', False, WHITE)
        WIN.blit(text_surface, (0, 0))
        text_surface = status_font.render(str(didziausias), False, WHITE)
        WIN.blit(text_surface, (400, 0))



def main():
    lentele = []
    for i in range(BOARD_SIZE):
        laikinas = []
        for j in range(BOARD_SIZE):
            laikinas.append(0)
        lentele.append(laikinas)

        
    didziausias = 1

    didziausias = naujas_skaicius(lentele, didziausias)
    didziausias = naujas_skaicius(lentele, didziausias)


    clock = pygame.time.Clock()
    run = True
    while run:
        clock.tick(FPS)
        isvesti_busena(lentele, didziausias)

        buvo_ivestis = False

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    pygame.quit()
                if event.key == pygame.K_LEFT:
                    didziausias = sutraukti_i_puse(3, lentele, didziausias)
                    buvo_ivestis = True
                    break
                if event.key == pygame.K_RIGHT:
                    didziausias = sutraukti_i_puse(1, lentele, didziausias)
                    buvo_ivestis = True
                    break
                if event.key == pygame.K_UP:
                    didziausias = sutraukti_i_puse(0, lentele, didziausias)
                    buvo_ivestis = True
                    break
                if event.key == pygame.K_DOWN:
                    didziausias = sutraukti_i_puse(2, lentele, didziausias)
                    buvo_ivestis = True
                    break

        if buvo_ivestis:
            Lentele_nepilna = False
            for i in range(0, 4):
                for j in range(0, 4):
                    if lentele[i][j] == 0:
                        Lentele_nepilna = True
            if Lentele_nepilna == False:
                didziausias = 4000

            didziausias = naujas_skaicius(lentele, didziausias)

if __name__ == "__main__":
    main()
