#include <bits/stdc++.h>

void writeInt(std::ofstream& fout, int val) {
  fout.write((char*)&val, sizeof(int));
}

void readInt(std::ifstream& fin, int &val) {
  fin.read((char*)&val, sizeof(int));
}

void writeShort(std::ofstream& fout, unsigned short val) {
  fout.write((char*)&val, sizeof(unsigned short));
}

int main(int argc, char** argv) {
  int playerx, playery;
  std::ifstream fin("level.in");
  std::ofstream fout(argv[1], std::ios::out | std::ios::binary);

  int background;
  fin >> background;
  writeInt(fout, background);

  fin >> playerx >> playery;
  writeInt(fout, playerx);
  writeInt(fout, playery);

  std::string str[16];
  for(int i = 0; i < 16; ++i) {
    fin >> str[i];
    std::cout << str[i] << std::endl;
  }

  for(int i = 0; i < 10; ++i) {
    unsigned short val = 0;
    for(int j = 0; j < 16; ++j)
      if(str[j][i] == '#')
        val = val | (1 << j);
    writeShort(fout, val);
  }

  int enemies;
  fin >> enemies;
  writeInt(fout, enemies);
  for(int i = 0; i < enemies; ++i) {
    int x, y;
    fin >> x >> y;
    writeInt(fout, x);
    writeInt(fout, y);
  }

  int activators;
  fin >> activators;
  writeInt(fout, activators);
  for(int i = 0; i < activators; ++i) {
    int x, y;
    fin >> x >> y;
    writeInt(fout, x);
    writeInt(fout, y);
  }

  int darttraps;
  fin >> darttraps;
  writeInt(fout, darttraps);
  for(int i = 0; i < darttraps; ++i) {
    int x, y, orientation, activator;
    fin >> x >> y >> orientation >> activator;
    writeInt(fout, x);
    writeInt(fout, y);
    writeInt(fout, orientation);
    writeInt(fout, activator);
  }

  fin.close();
  fout.close();
  return 0;
}

/*
background
playerx playery
wallmap
enemies
enemy[i].x enemy[i].y
activators
activator[i].x activator[i].y
darttraps
darttrap[i].x darttrap[i].y darttrap[i].orientation darttrap[i].activator
*/
