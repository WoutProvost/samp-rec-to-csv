# samp-rec-to-csv
File format converter from `.rec` to `.csv` and vice versa, which NPCs use in SA-MP to play back recordings.

This tool can be used to edit `.rec` files after recording the data:
1. convert to `.csv` using `rec2csv`
2. edit the `.csv` in something like Microsoft Excel or Google Spreadsheets
3. convert back to `.rec` using `csv2rec`

Special thanks to Mauzen for his work on figuring out and [documenting](https://team.sa-mp.com/wiki/.rec_file.html) the `.rec` file structure and Y_Less for YSI in which these structures are also defined.

### Building
```bash
mkdir build
cd build
cmake ..
make
```

### Running
```bash
./rec2csv -h
./csv2rec -h
```