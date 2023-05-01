import pygame
 
def init():
    pygame.init()
    win = pygame.display.set_mode((100,100))
 
def getKey(keyName):
    ans = False
    for eve in pygame.event.get():pass
    keyInput = pygame.key.get_pressed()
    myKey = getattr(pygame,'K_{}'.format(keyName))
    if keyInput [myKey]:
        ans = True
    pygame.display.update()
 
    return ans
 
def main():
    if getKey('w') & getKey('a'):
        print("FORWARD LEFT")
    if getKey('w') & getKey('d'):
        print("FORWARD RIGHT")
 
    if getKey('a'):
        print('LEFT')
    if getKey('d'):
        print('RIGHT')
    if getKey('w'):
        print("FORWARD")
    if getKey('s'):
        print("BACKWARD")
    if getKey('SPACE'):
        print("STOPPED")
 
if __name__ == '__main__':
    init()
    while True:
        main()