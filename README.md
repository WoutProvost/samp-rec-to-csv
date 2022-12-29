# samp-rec-to-csv
File format converter from `.rec` to `.csv` and vice versa, which NPCs use in SA-MP to play back recordings.

Special thanks to Mauzen for his work on figuring out and documeting the `.rec` file structure: https://team.sa-mp.com/wiki/.rec_file.html or https://sampwiki.blast.hk/wiki/.rec_file.

### Building
```bash
mkdir build
cd build
cmake ..
make
```

### Running
```bash
./rec2csv
./csv2rec
```