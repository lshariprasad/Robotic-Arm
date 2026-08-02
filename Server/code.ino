#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// ================= TFT pins =================
#define TFT_CS   15
#define TFT_DC    2
#define TFT_RST   4
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST); // Fixed typo here

// ================= Buttons + Buzzer =================
#define BTN1 32   // also used as JUMP in Dino game
#define BTN2 33
#define BTN3 12
#define BTN4 13
#define BUZZER 27

// ================= Screen layout constants =================
#define SCREEN_W 128
#define SCREEN_H 160
#define HEADER_H 16
#define FOOTER_H 16
#define MARGIN 4

// Content area limits
#define CONTENT_Y (HEADER_H + MARGIN)
#define CONTENT_BOTTOM (SCREEN_H - FOOTER_H - MARGIN)

// Text properties
#define TEXT_SIZE 1
#define CHAR_W 6   // default GFX font: 6px advance per char at size 1
#define LINE_H 10  // vertical space between lines
#define OPTION_GAP 12

// ================= High-Contrast Colors =================
#define BG          ST77XX_BLACK
#define COL_HEADER  tft.color565(15, 20, 60)   // Deep Indigo
#define COL_FOOTER  tft.color565(15, 20, 60)   // Deep Indigo
#define COL_TEXT    ST77XX_WHITE
#define COL_GOLD    tft.color565(255, 215, 0)
#define COL_KEYWORD tft.color565(255, 60, 60)  // Bright Red
#define COL_OPTION  tft.color565(50, 200, 255) // Cyan
#define COL_CORRECT tft.color565(30, 220, 80)  // Bright Green
#define COL_WRONG   tft.color565(220, 50, 50)  // Bright Red
#define COL_HEART   tft.color565(255, 80, 110) // Pink-Red
#define COL_GRAY    tft.color565(60, 60, 60)

// ================= Question bank =================
struct Question {
  const char* text;
  const char* opt[4];
  int correct;
  const char* keyword1;   // word(s) to highlight red, "" if none
  const char* keyword2;
};

Question quiz[] = {
  {"Gauss-Seidel is what type of method for solving equations?",
   {"[1] Direct", "[2] Iterative", "[3] Graphical", "[4] Random"}, 1, "Gauss-Seidel", "Iterative"},

  {"Gauss-Seidel differs from Jacobi because it uses updated values immediately",
   {"[1] True", "[2] False", "[3] Sometimes", "[4] Never"}, 0, "Gauss-Seidel", "Jacobi"},

  {"Gauss-Seidel is guaranteed to converge when the matrix is diagonally dominant",
   {"[1] True", "[2] False", "[3] Only 2x2", "[4] Never"}, 0, "diagonally", "dominant"},

  {"In cloud load balancing the unknowns represent load on each node",
   {"[1] True", "[2] False", "[3] Cost only", "[4] Neither"}, 0, "load", "balancing"},

  {"Why use iterative methods for large cloud systems?",
   {"[1] Always exact", "[2] Great for sparse", "[3] No computer needed", "[4] Avoids matrices"}, 1, "iterative", ""},

  {"Gauss-Seidel iteration stops when error is below tolerance",
   {"[1] True", "[2] False", "[3] At boot", "[4] Never"}, 0, "tolerance", ""},

  {"Approx cost per Gauss-Seidel iteration is:",
   {"[1] O(1)", "[2] O(log n)", "[3] O(n^2)", "[4] O(n!)"}, 2, "Gauss-Seidel", ""},

  {"Faster convergence in load balancing means quicker optimal load spread",
   {"[1] True", "[2] False", "[3] Slower", "[4] No effect"}, 0, "convergence", "load"},

  {"A good initial guess in Gauss-Seidel mainly helps faster convergence",
   {"[1] True", "[2] False", "[3] Slower", "[4] No effect"}, 0, "convergence", ""},

  {"Gauss-Seidel needs the matrix to represent load balancing equations",
   {"[1] True", "[2] False", "[3] Server IP", "[4] Passwords"}, 0, "load", "balancing"},

  {"Compared to direct methods Gauss-Seidel uses less memory for large sparse systems",
   {"[1] True", "[2] False", "[3] Same memory", "[4] More memory"}, 0, "sparse", ""},

  {"A real benefit of this method in cloud systems is scaling well for many servers",
   {"[1] True", "[2] False", "[3] Removes servers", "[4] Offline only"}, 0, "scaling", "servers"}
};

const int totalQuestions = sizeof(quiz) / sizeof(quiz[0]);
int score = 0;
int heartPoints = 6;    // 3 hearts x 2 points each. -1 per wrong, +2 per correct (capped at 6)
bool gameOver = false;

// ================= Buzzer melodies =================
void playIntroSound() {
  int notes[] = {700, 900, 1100};
  int durs[]  = {100, 100, 160};
  for (int i = 0; i < 3; i++) { tone(BUZZER, notes[i], durs[i]); delay(durs[i] + 30); }
  noTone(BUZZER);
}
void playCorrectSound() {
  int notes[] = {1500, 2000};
  int durs[]  = {80, 130};
  for (int i = 0; i < 2; i++) { tone(BUZZER, notes[i], durs[i]); delay(durs[i] + 20); }
  noTone(BUZZER);
}
void playWrongSound() {
  int notes[] = {450, 350};
  int durs[]  = {120, 160};
  for (int i = 0; i < 2; i++) { tone(BUZZER, notes[i], durs[i]); delay(durs[i] + 20); }
  noTone(BUZZER);
}
void playFinaleSound() {
  int notes[] = {1000, 1200, 1500, 1800};
  int durs[]  = {100, 100, 100, 200};
  for (int i = 0; i < 4; i++) { tone(BUZZER, notes[i], durs[i]); delay(durs[i] + 20); }
  noTone(BUZZER);
}
void playHeartBreakSound() {
  tone(BUZZER, 300, 200); delay(220);
  noTone(BUZZER);
}
void playJumpSound() {
  tone(BUZZER, 900, 60); delay(60);
  noTone(BUZZER);
}

// ================= Drawing helpers =================

// Draws a clean, full-width header bar
void drawHeader(int qIndex) {
  tft.fillRect(0, 0, SCREEN_W, HEADER_H, COL_HEADER);
  
  tft.setTextSize(TEXT_SIZE);
  tft.setTextColor(COL_GOLD);
  tft.setCursor(MARGIN, 4);
  tft.print("Q:");
  tft.setTextColor(COL_TEXT);
  tft.print(qIndex + 1);
  tft.print("/");
  tft.print(totalQuestions);

  tft.setTextColor(COL_GOLD);
  tft.setCursor(SCREEN_W - 40, 4);
  tft.print("S:");
  tft.setTextColor(COL_TEXT);
  tft.print(score);
}

// Draws modern, clean hearts in the footer
void drawHeart(int x, int y, int size, int state) {
  uint16_t color = (state > 0) ? COL_HEART : COL_GRAY;
  int r = size / 2;
  
  // Two circles for the top humps
  tft.fillCircle(x - r, y - 1, r, color);
  tft.fillCircle(x + r, y - 1, r, color);
  // Triangle for the bottom point
  tft.fillTriangle(x - size, y, x + size, y, x, y + size, color);

  // If half heart, cut the right side out using the footer background color
  if (state == 1) {
    tft.fillRect(x, y - size, size + 2, size * 2 + 2, COL_FOOTER);
  }
}

void drawFooterHearts() {
  tft.fillRect(0, SCREEN_H - FOOTER_H, SCREEN_W, FOOTER_H, COL_FOOTER);
  int cy = SCREEN_H - FOOTER_H / 2 - 2;
  int startX = SCREEN_W - 45;
  
  for (int i = 0; i < 3; i++) {
    int state = 0;
    if (heartPoints >= 6 - i * 2) state = 2;       // Full
    else if (heartPoints == 5 - i * 2) state = 1;  // Half
    
    drawHeart(startX + i * 14, cy, 4, state);
  }
}

void drawStar(int x, int y, int r, uint16_t color) {
  for (int i = 0; i < 5; i++) {
    float a1 = i * 2 * PI / 5 - PI / 2;
    float a2 = (i + 2) * 2 * PI / 5 - PI / 2;
    tft.drawLine(x + r * cos(a1), y + r * sin(a1), x + r * cos(a2), y + r * sin(a2), color);
  }
}

// ================= Left-Aligned Word-Wrapped Text =================
bool isKeyword(const char* word, const char* k1, const char* k2) {
  char clean[24];
  int len = strlen(word);
  int j = 0;
  for (int i = 0; i < len && j < 23; i++) {
    if (isalnum((unsigned char)word[i]) || word[i] == '-') clean[j++] = word[i];
  }
  clean[j] = '\0';
  if (k1[0] != '\0' && strcasecmp(clean, k1) == 0) return true;
  if (k2[0] != '\0' && strcasecmp(clean, k2) == 0) return true;
  return false;
}

// Prints normal left-aligned, word-wrapped text. Highlights keywords red.
int printTextColored(const char* text, int y, const char* k1, const char* k2) {
  char buf[160];
  strncpy(buf, text, sizeof(buf) - 1);
  buf[sizeof(buf) - 1] = '\0';

  char* words[30];
  int wordCount = 0;
  char* tok = strtok(buf, " ");
  while (tok != NULL && wordCount < 30) {
    words[wordCount++] = tok;
    tok = strtok(NULL, " ");
  }

  int i = 0;
  tft.setTextSize(TEXT_SIZE);
  while (i < wordCount) {
    int lineStart = i;
    int lineWidth = 0;
    while (i < wordCount) {
      int wWidth = strlen(words[i]) * CHAR_W;
      int extra = (i > lineStart) ? CHAR_W : 0; // space before word
      if (lineWidth + extra + wWidth > SCREEN_W - 2 * MARGIN && i > lineStart) break;
      lineWidth += extra + wWidth;
      i++;
    }
    
    int x = MARGIN;
    for (int w = lineStart; w < i; w++) {
      uint16_t color = isKeyword(words[w], k1, k2) ? COL_KEYWORD : COL_TEXT;
      tft.setTextColor(color);
      tft.setCursor(x, y);
      tft.print(words[w]);
      x += strlen(words[w]) * CHAR_W + CHAR_W;
    }
    y += LINE_H;
  }
  return y;
}

// Prints an option line in Cyan
void printOption(const char* text, int y) {
  tft.setTextSize(TEXT_SIZE);
  tft.setTextColor(COL_OPTION);
  tft.setCursor(MARGIN, y);
  tft.print(text);
}

// ================= Question screen =================
void showQuestion(int qIndex) {
  tft.fillScreen(BG);
  drawHeader(qIndex);

  int y = CONTENT_Y;
  y = printTextColored(quiz[qIndex].text, y, quiz[qIndex].keyword1, quiz[qIndex].keyword2);
  y += 4; // Small gap

  // Subtle separator line
  tft.drawFastHLine(MARGIN, y, SCREEN_W - 2 * MARGIN, COL_GRAY);
  y += 4;

  for (int i = 0; i < 4; i++) {
    printOption(quiz[qIndex].opt[i], y);
    y += OPTION_GAP;
  }

  drawFooterHearts();
}

int waitForAnswer() {
  while (true) {
    if (digitalRead(BTN1) == LOW) { delay(200); return 0; }
    if (digitalRead(BTN2) == LOW) { delay(200); return 1; }
    if (digitalRead(BTN3) == LOW) { delay(200); return 2; }
    if (digitalRead(BTN4) == LOW) { delay(200); return 3; }
    delay(10);
  }
}

void correctAnimation() {
  tft.fillRect(0, SCREEN_H/2 - 12, SCREEN_W, 24, tft.color565(0, 40, 0)); // Dark green box
  tft.setTextSize(2);
  tft.setTextColor(COL_CORRECT);
  const char* msg = "YES!";
  int w = strlen(msg) * 12; // 6px * size 2
  tft.setCursor((SCREEN_W - w)/2, SCREEN_H/2 - 8);
  tft.println(msg);
  playCorrectSound();
  delay(600);
}

void wrongAnimation() {
  tft.fillRect(0, SCREEN_H/2 - 12, SCREEN_W, 24, tft.color565(50, 0, 0)); // Dark red box
  tft.setTextSize(2);
  tft.setTextColor(COL_WRONG);
  const char* msg = "NO!";
  int w = strlen(msg) * 12;
  tft.setCursor((SCREEN_W - w)/2, SCREEN_H/2 - 8);
  tft.println(msg);
  playWrongSound();
  playHeartBreakSound();
  delay(600);
}

// ================= Dino mini-game (20 sec break, BTN1 = jump) =================
void playDinoGame() {
  // Keep header and footer intact, clear only the content area
  tft.fillRect(0, HEADER_H, SCREEN_W, SCREEN_H - HEADER_H - FOOTER_H, BG);

  tft.setTextSize(1);
  tft.setTextColor(COL_GOLD);
  tft.setCursor(MARGIN, CONTENT_Y);
  tft.println("Bonus Round!");
  tft.setTextColor(COL_TEXT);
  tft.setCursor(MARGIN, CONTENT_Y + 12);
  tft.println("BTN1 to Jump");
  delay(1500);

  int groundY = SCREEN_H - FOOTER_H - 4;
  int dinoX = MARGIN + 2, dinoY = groundY - 8, dinoSize = 8;
  float velY = 0;
  bool jumping = false;
  const float gravity = 0.9;
  const float jumpVel = -7.5;

  int obsX = SCREEN_W - 10;
  int obsW = 6, obsH = 12;
  int obsSpeed = 3;

  unsigned long startTime = millis();
  unsigned long lastFrame = millis();
  bool alive = true;

  while (millis() - startTime < 20000 && alive) {
    if (millis() - lastFrame < 40) continue; // ~25fps
    lastFrame = millis();

    if (digitalRead(BTN1) == LOW && !jumping) {
      jumping = true;
      velY = jumpVel;
      playJumpSound();
    }

    if (jumping) {
      dinoY += velY;
      velY += gravity;
      if (dinoY >= groundY - dinoSize) {
        dinoY = groundY - dinoSize;
        jumping = false;
        velY = 0;
      }
    }

    obsX -= obsSpeed;
    if (obsX < MARGIN) obsX = SCREEN_W - MARGIN;

    // collision check
    bool hit = (obsX < dinoX + dinoSize && obsX + obsW > dinoX &&
                dinoY + dinoSize > groundY - obsH);
    if (hit) alive = false;

    // draw frame (clear content area only)
    tft.fillRect(0, HEADER_H, SCREEN_W, SCREEN_H - HEADER_H - FOOTER_H, BG);
    
    tft.drawFastHLine(MARGIN, groundY, SCREEN_W - 2 * MARGIN, COL_GRAY);
    tft.fillRect(dinoX, dinoY, dinoSize, dinoSize, COL_GOLD); // Dino
    tft.fillRect(obsX, groundY - obsH, obsW, obsH, COL_OPTION); // Obstacle
  }

  tft.fillRect(0, HEADER_H, SCREEN_W, SCREEN_H - HEADER_H - FOOTER_H, BG);
  tft.setTextSize(1);
  tft.setTextColor(COL_GOLD);
  tft.setCursor(MARGIN, CONTENT_Y + 8);
  tft.println(alive ? "Time's up!" : "Ouch! Nice try!");
  delay(1000);
}

// ================= Final score =================
void showFinalScore() {
  tft.fillScreen(BG);
  drawHeader(totalQuestions - 1); // Keep header consistent
  
  int y = 30;
  tft.setTextSize(2);
  tft.setTextColor(gameOver ? COL_WRONG : COL_CORRECT);
  const char* title = gameOver ? "GAME OVER" : "COMPLETE!";
  int titleW = strlen(title) * 12; // size 2 width
  tft.setCursor((SCREEN_W - titleW)/2, y);
  tft.println(title);
  y += 28;

  tft.setTextSize(1);
  tft.setTextColor(COL_TEXT);
  tft.setCursor(MARGIN, y);
  tft.print("Score: ");
  tft.setTextColor(COL_GOLD);
  tft.print(score);
  tft.print("/");
  tft.println(totalQuestions);
  y += 15;

  int pct = (score * 100) / totalQuestions;
  int starCount = (pct >= 90) ? 5 : (pct >= 75) ? 4 : (pct >= 50) ? 3 : (pct >= 25) ? 2 : 1;
  for (int i = 0; i < 5; i++) {
    uint16_t c = (i < starCount) ? COL_GOLD : COL_GRAY;
    drawStar(20 + i * 18, y + 8, 5, c);
  }
  y += 24;

  tft.setTextColor(COL_TEXT);
  const char* msg;
  if (pct >= 90) msg = "Outstanding!";
  else if (pct >= 75) msg = "Great job!";
  else if (pct >= 50) msg = "Nice effort!";
  else msg = "Keep it up!";
  
  int mw = strlen(msg) * CHAR_W;
  tft.setCursor((SCREEN_W - mw)/2, y);
  tft.println(msg);

  drawFooterHearts(); // Draw bottom bar
  tft.setTextColor(COL_GOLD);
  const char* replayMsg = "BTN1 to Replay";
  int rw = strlen(replayMsg) * CHAR_W;
  tft.setCursor((SCREEN_W - rw)/2, SCREEN_H - FOOTER_H + 4);
  tft.println(replayMsg);

  if (pct >= 75) {
    playFinaleSound();
    for (int i = 0; i < 30; i++) {
      int x = random(MARGIN, SCREEN_W - MARGIN);
      int yy = random(HEADER_H + 70, SCREEN_H - FOOTER_H - 4);
      uint16_t c = random(0, 2) ? COL_GOLD : COL_KEYWORD;
      tft.fillRect(x, yy, 2, 2, c);
      delay(10);
    }
  } else {
    playCorrectSound();
  }
}

// ================= Intro =================
void showIntro() {
  tft.fillScreen(BG);
  drawHeader(0);
  drawFooterHearts();

  tft.setTextSize(2);
  tft.setTextColor(COL_GOLD);
  tft.setCursor(10, 40);
  tft.println("Numerical");
  tft.setCursor(25, 58);
  tft.println("Methods");

  tft.setTextSize(1);
  tft.setTextColor(COL_TEXT);
  tft.setCursor(35, 80);
  tft.println("Quiz Time!");

  tft.setTextColor(COL_KEYWORD);
  tft.setCursor(5, 100);
  tft.println("Gauss-Seidel Method");
  tft.setCursor(10, 110);
  tft.println("& Load Balancing");

  // Animated stars
  for (int i = 0; i < 3; i++) {
    drawStar(30 + i * 30, 130, 5, COL_GOLD);
    delay(150);
  }
  playIntroSound();
  delay(1000);
}

// ================= Setup / Loop =================
void setup() {
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);
  pinMode(BTN4, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  randomSeed(analogRead(0));

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(0);
  tft.fillScreen(BG);

  showIntro();
}

void loop() {
  score = 0;
  heartPoints = 6;
  gameOver = false;

  for (int i = 0; i < totalQuestions; i++) {
    showQuestion(i);
    int answer = waitForAnswer();
    bool correct = (answer == quiz[i].correct);

    if (correct) {
      score++;
      heartPoints += 2;
      if (heartPoints > 6) heartPoints = 6;
      correctAnimation();
    } else {
      heartPoints -= 1;
      if (heartPoints < 0) heartPoints = 0;
      wrongAnimation();
    }
    
    // Update hearts immediately after the answer animation
    drawFooterHearts();

    if (heartPoints <= 0) {
      gameOver = true;
      break;
    }

    if (i == 5 && !gameOver) {  // after question 6
      playDinoGame();
    }
  }

  showFinalScore();

  // Wait for BTN1 to restart
  while (digitalRead(BTN1) == HIGH) delay(50);
  delay(300);
}
