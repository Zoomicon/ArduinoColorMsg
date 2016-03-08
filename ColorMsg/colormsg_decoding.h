/*
 * Decoding functions
 * 
 * Components:
 *   Arduino board
 */

#define ESC 27

/*
 * Map consequtive color names (Red or Green or Blue) to a letter and the remaining combinations to some extra symbols
 */
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
  'B', 'G', 'G',   'W',
  'B', 'G', 'B',   'X',

  'B', 'B', 'R',   'Y',
  'B', 'B', 'G',   'Z',
  'B', 'B', 'B',   ESC
};

#define buffer_length 3
#define code_row_length (buffer_length + 1)
#define code_length ((sizeof code) / (sizeof (char)) / code_row_length)

/*
 * Variables
 */
char color_name_buffer[buffer_length] = {' ', ' ', ' '};
int buffer_pos = 0;

/*
 * Decode a full color_name_buffer
 */
char decode_color_name_buffer() {
  //for each code row
  for (int row = 0; row < code_length; row++){
    bool match = true;
    int row_pos = row * code_row_length;

    //for each character in buffer
    for (int i = 0 ; i < buffer_length; i++)
      if (color_name_buffer[i] != code[row_pos + i]){
        match = false; //found mismatch
        break; //don't check the rest of the row
      }
     
    if (match)
      return code[row_pos + buffer_length];
  }

  return 0;
}

/*
 * Push color name into color_name_buffer and return result of buffer decoding when it is full, then recycle
 */
char decode_color_name(bool isRed, bool isGreen, bool isBlue) {
  char c = 0;

  //we only care for Red or Green or Blue color (separately) as input, so if more than one are detected, pick just one in this order: Red, Green, Blue
  if (isRed)
    c = 'R';
  else if(isGreen)
    c = 'G';
  else if (isBlue)
    c = 'B';

  if (c != 0) {
    color_name_buffer[buffer_pos] = c;

    bool buffer_full = (buffer_pos == (buffer_length - 1)); //must check this before updating buffer_pos
    buffer_pos = (buffer_pos + 1) % buffer_length;

    if (buffer_full)
      return decode_color_name_buffer(); //must do this after having updated buffer_pos
  }

  return 0;
}

