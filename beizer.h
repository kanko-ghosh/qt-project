#ifndef BEIZER_H
#define BEIZER_H

long long comb(int n, int r)
{
    if (r > n - r)
        r = n - r;

    long long C[r + 1];
    memset(C, 0, sizeof(C));

    C[0] = 1;

    for (int i = 1; i <= n; i++) {

        for (int j = std::min(i, r); j > 0; j--)
            C[j] = (C[j] + C[j - 1]);
    }
    return C[r];
}

float BEZ(int k, int n, float u) {
    return (float)(comb(n, k) * pow(u, k) * pow(1 - u, n - k));
}

void MainWindow::on_beizer_curve_button_clicked()
{
    if (this->to_do == 1){
        //drawing polygon
        this->to_do = 11;
        polygon.resize(0);
        return;
    }

    this->to_do = 1;
    if (polygon.size() < 2) {
        ui->time_show->setText(QString::number(0));
        return;
    }

    int n = polygon.size() - 1;
    float du = ui->beizer_coeff->value();
    if (du == 0) du = 0.1;
    bool firstPointDone = false;
    float xPrev = -1;
    float yPrev = -1;

    for (float u = 0; u <= 1.0 + du / 2; u += du){
        float x = 0;
        float y = 0;

        for(int k = 0; k <= n; k++)
        {
            float coeff = BEZ(k, n, u);
            x += polygon[k].first * coeff;
            y += polygon[k].second * coeff;
        }

        if(firstPointDone) _dda_line(x, y, xPrev, yPrev);

        xPrev = x;
        yPrev = y;
        firstPointDone = true;
    }

    ui->frame->setPixmap(QPixmap::fromImage(img));


    timer.start();
    for (float u = 0; u <= 1.0 + du / 2; u += du){
        float x = 0;
        float y = 0;

        for(int k = 0; k <= n; k++)
        {
            float coeff = BEZ(k, n, u);
            x += polygon[k].first * coeff;
            y += polygon[k].second * coeff;
        }

        xPrev = x;
        yPrev = y;
    }
    auto time = timer.nsecsElapsed();
    ui->time_show->setText(QString::number(time));

}




#endif // BEIZER_H
