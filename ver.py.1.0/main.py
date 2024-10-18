import numpy as np
import tetris.tetris as tetris
import time
# import time
# import example


def main():
  
  # print()


  # Block = tetris.Block("S")

  # Grid.grid[1:(1+4), 3:(3+4)] += Block.block
  # print(Block)

  # Block.__rotate__(True)

  # print(Block)

  profile = tetris.Settings()
  Grid = tetris.GridWorld(profile)

  BL = tetris.BlockLists(profile=profile)
  # BL.append("L")
  BL.append("O")
  BL.append("T")

  BL.print_list()
  
  # print(Grid)
  # BL.print_list()

  while not profile.GameIsOver:
    print(Grid, flush=True)
    
    # if True: BL.join(Grid)
    # print(BL.TouchBottom(Grid))

    if not profile.GameIsStarted: BL.join(Grid)

    # BL.head.__move__("N", profile.GameSpeed)
    time.sleep(1)

  


if __name__ == "__main__":
  main()
