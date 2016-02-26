#define buffer_length 3
#define code_row_length (buffer_length + 1)

char code[] = {
  'R', 'R', 'R',   'A',
  'R', 'R', 'G',   'B',
  'R', 'R', 'B',   'C',

  'R', 'G', 'R',   'D',
  'R', 'G', 'G',   'E',
  'R', 'G', 'B',   'F',

  'R', 'B', 'R',   'G',
  'R', 'B', 'G',   'H',
  'R', 'B', 'B',   'I',

  //

  'G', 'R', 'R',   'J',
  'G', 'R', 'G',   'K',
  'G', 'R', 'B',   'L',

  'G', 'G', 'R',   'M',
  'G', 'G', 'G',   'N',
  'G', 'G', 'B',   'O',

  'G', 'B', 'R',   'P',
  'G', 'B', 'G',   'Q',
  'G', 'B', 'B',   'R',  

  //

  'B', 'R', 'R',   'S',
  'B', 'R', 'G',   'T',
  'B', 'R', 'B',   'U',

  'B', 'G', 'R',   'V',
  'B', 'G', 'G',   'X',
  'B', 'G', 'B',   'Y',

  'B', 'B', 'R',   'Z',
  'B', 'B', 'G',   ' ',
  'B', 'B', 'B',   '*'
};

#define code_length ((sizeof code) / (sizeof (char)) / code_row_length)

char color_buffer[buffer_length] = {' ', ' ', ' '};
int buffer_pos = 0;

char decode_color_from_code(){
  //for each code row
  for (int row = 0; row < code_length; row++){
    bool match = true;
    int row_pos = row * code_row_length;

    //for each character in buffer
    for (int i = 0 ; i < buffer_length; i++)
      if (color_buffer[i] != code[row_pos + i]){
        match = false; //found mismatch
        break; //don't check the rest of the row
      }
     
    if (match)
      return code[row_pos + buffer_length];
  }

  return 0;
}

char decode_color(bool isRed, bool isGreen, bool isBlue){
  char c = 0;
   
  if (isRed)
    c = 'R';
  else if(isGreen)
    c = 'G';
  else if (isBlue)
    c = 'B';

  if (c != 0) {
    color_buffer[buffer_pos] = c;

    bool buffer_full = (buffer_pos == (buffer_length - 1)); //must check this before updating buffer_pos
    buffer_pos = (buffer_pos + 1) % buffer_length;

    if (buffer_full)
      return decode_color_from_code(); //must do this after having updated buffer_pos
  }

  return 0;
}

