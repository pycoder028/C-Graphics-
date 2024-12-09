#include <graphics.h>
#include <conio.h>
#include <dos.h>

// Function to draw the road layout
void drawRoad() {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, DARKGRAY);

    // Draw horizontal road
    bar(0, 200, 640, 280);

    // Draw vertical road
    bar(280, 0, 360, 480);

    // Draw road dividers
    setcolor(WHITE);
    for (int i = 10; i < 640; i += 40)
        line(i, 240, i + 20, 240); // Horizontal divider

    for (int j = 10; j < 480; j += 40)
        line(320, j, 320, j + 20); // Vertical divider
}

// Function to draw a traffic light
void drawTrafficLight(int x, int y, int state) {
    setcolor(WHITE);
    rectangle(x, y, x + 30, y + 90); // Traffic light box
    setfillstyle(SOLID_FILL, BLACK);
    bar(x, y, x + 30, y + 90); // Fill black background

    if (state == 1) {
        setfillstyle(SOLID_FILL, RED);
        fillellipse(x + 15, y + 15, 10, 10); // Red light
    } else if (state == 2) {
        setfillstyle(SOLID_FILL, YELLOW);
        fillellipse(x + 15, y + 45, 10, 10); // Yellow light
    } else if (state == 3) {
        setfillstyle(SOLID_FILL, GREEN);
        fillellipse(x + 15, y + 75, 10, 10); // Green light
    }
}

// Function to draw cars
void drawCar(int x, int y, int color) {
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    rectangle(x, y, x + 40, y + 20);    // Car body
    rectangle(x + 10, y - 10, x + 30, y); // Car roof
    fillellipse(x + 10, y + 20, 5, 5); // Wheels
    fillellipse(x + 30, y + 20, 5, 5);
}

// Function to move cars based on signal
void moveCars(int signalHorizontal, int signalVertical) {
    int carX1 = 0, carX2 = 600, carY1 = 0, carY2 = 400;
    int speed = 5;

    while (!kbhit()) {
        cleardevice();
        drawRoad();

        // Draw traffic lights
        drawTrafficLight(250, 150, signalHorizontal); // Top left
        drawTrafficLight(250, 320, signalVertical);   // Bottom left
        drawTrafficLight(390, 150, signalHorizontal); // Top right
        drawTrafficLight(390, 320, signalVertical);   // Bottom right

        // Draw and move cars
        if (signalHorizontal == 3) // Green light for horizontal
            carX1 += speed;
        if (signalVertical == 3) // Green light for vertical
            carY1 += speed;

        if (signalHorizontal != 3) // Stop horizontal cars at red/yellow
            carX1 = (carX1 >= 250 && carX1 <= 350) ? carX1 : carX1 + speed;
        if (signalVertical != 3) // Stop vertical cars at red/yellow
            carY1 = (carY1 >= 150 && carY1 <= 250) ? carY1 : carY1 + speed;

        drawCar(carX1, 230, BLUE); // Horizontal car (left to right)
        drawCar(600 - carX1, 260, RED); // Horizontal car (right to left)
        drawCar(310, carY1, GREEN); // Vertical car (top to bottom)
        drawCar(340, 400 - carY1, YELLOW); // Vertical car (bottom to top)

        delay(50);

        // Reset positions if cars move off screen
        if (carX1 > 640) carX1 = 0;
        if (carY1 > 480) carY1 = 0;
    }
}

int main() {
    int gd = DETECT, gm;

    // Initialize graphics mode
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    while (true) {
        // Simulate red for horizontal, green for vertical
        moveCars(1, 3);
        delay(2000);

        // Simulate yellow for all
        moveCars(2, 2);
        delay(2000);

        // Simulate green for horizontal, red for vertical
        moveCars(3, 1);
        delay(2000);

        // Simulate yellow for all
        moveCars(2, 2);
        delay(2000);
    }

    getch();
    closegraph();
    return 0;
}
