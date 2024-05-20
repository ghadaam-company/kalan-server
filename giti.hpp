
            }
            if (src_y > src_h - 2)
            {
                ratio_y[0] = 0;
                src_y = src_h - 2;
            }
            ratio_y[1] = 1 - ratio_y[0]; // y2 - y

            int _dst_i = y * dst_w;

            int _src_row_0 = src_y * src_w;
            int _src_row_1 = _src_row_0 + src_w;

            for (size_t x = x_start; x < x_end; x++)
            {
                float ratio_x[2];
                ratio_x[0] = (float)((x + 0.5) * scale_x - 0.5); // x
                int src_x = (int)ratio_x[0];                     // x1
                ratio_x[0] -= src_x;                             // x - x1

                if (src_x < 0)
                {
                    ratio_x[0] = 0;
                    src_x = 0;
                }
                if (src_x > src_w - 2)
                {
                    ratio_x[0] = 0;
                    src_x = src_w - 2;
                }
                ratio_x[1] = 1 - ratio_x[0]; // x2 - x

                int dst_i = (_dst_i + x) * channel;

                int src_row_0 = _src_row_0 + src_x;
                int src_row_1 = _src_row_1 + src_x;

                Image<int>::pixel_rgb565_to_rgb888(src_image[src_row_0], temp);
                Image<int>::pixel_rgb565_to_rgb888(src_image[src_row_0 + 1], temp + 3);
                Image<int>::pixel_rgb565_to_rgb888(src_image[src_row_1], temp + 6);
                Image<int>::pixel_rgb565_to_rgb888(src_image[src_row_1 + 1], temp + 9);

                for (int c = 0; c < channel; c++)
                {
                    temp[12] = round(temp[c] * ratio_x[1] * ratio_y[1] + temp[channel + c] * ratio_x[0] * ratio_y[1] + temp[channel + channel + c] * ratio_x[1] * ratio_y[0] + src_image[channel + channel + channel + c] * ratio_x[0] * ratio_y[0]);
                    dst_image[dst_i + c] = (shift_left > 0) ? (temp[12] << shift_left) : (temp[12] >> -shift_left);
                }
            }
        }
        break;

    case IMAGE_RESIZE_MEAN:
        shift_left -= 2;
        for (int y = y_start; y < y_end; y++)
        {
            int _dst_i = y * dst_w;

            float _src_row_0 = rintf(y * scale_y) * src_w;
            float _src_row_1 = _src_row_0 + src_w;

            for (int x = x_start; x < x_end; x++)
            {
                int dst_i = (_dst_i + x) * channel;

                int src_row_0 = (_src_row_0 + rintf(x * scale_x));
                int src_row_1 = (_src_row_1 + rintf(x * scale_x));

                Image<int>::pixel_rgb565_to_rgb888(src_image[src_row_0], temp);
                Image<int>::pixel_rgb565_to_rgb888(src_image[src_row_0 + 1], temp + 3);
                Image<int>::pixel_rgb565_to_rgb888(src_image[src_row_1], temp + 6);
                Image<int>::pixel_rgb565_to_rgb888(src_image[src_row_1 + 1], temp + 9);

                dst_image[dst_i] = (shift_left > 0) ? ((temp[0] + temp[3] + temp[6] + temp[9]) << shift_left) : ((temp[0] + temp[3] + temp[6] + temp[9]) >> -shift_left);
                dst_image[dst_i + 1] = (shift_left > 0) ? ((temp[1] + temp[4] + temp[7] + temp[10]) << shift_left) : ((temp[1] + temp[4] + temp[7] + temp[10]) >> -shift_left);
                dst_image[dst_i + 2] = (shift_left > 0) ? ((temp[2] + temp[5] + temp[8] + temp[11]) << shift_left) : ((temp[1] + temp[4] + temp[7] + temp[10]) >> -shift_left);
            }
        }

        break;

    case IMAGE_RESIZE_NEAREST:
        for (size_t y = y_start; y < y_end; y++)
        {
            int _dst_i = y * dst_w;
            float _src_i = rintf(y * scale_y) * src_w;

            for (size_t x = x_start; x < x_end; x++)
            {
                int dst_i = (_dst_i + x) * channel;
                int src_i = _src_i + rintf(x * scale_x);

                Image<int>::pixel_rgb565_to_rgb888(src_image[src_i], temp);

                dst_image[dst_i] = (shift_left > 0) ? (temp[0] << shift_left) : (temp[0] >> -shift_left);
                dst_image[dst_i + 1] = (shift_left > 0) ? (temp[1] << shift_left) : (temp[1] >> -shift_left);
                dst_image[dst_i + 2] = (shift_left > 0) ? (temp[2] << shift_left) : (temp[2] >> -shift_left);
            }
        }
        break;

    default:
        break;
    }
}

template <class T>
void Image<T>::resize_to_rgb888(T *dst_image, int y_start, int y_end, int x_start, int x_end, int channel, uint8_t *src_image, int src_h, int src_w, int dst_w, int shift_left, image_resize_t type)
{
    float scale_y = (float)src_h / (y_end - y_start);
    float scale_x = (float)src_w / (x_end - x_start);
    int temp;

    switch (type)
    {
    case IMAGE_RESIZE_BILINEAR:
        for (size_t y = y_start; y < y_end; y++)
        {
            float ratio_y[2];
            ratio_y[0] = (float)((y + 0.5) * scale_y - 0.5); // y
            int src_y = (int)ratio_y[0];                     // y1
            ratio_y[0] -= src_y;                             // y - y1

            if (src_y < 0)
            {
                ratio_y[0] = 0;
                src_y = 0;
            }
            if (src_y > src_h - 2)
            {
                ratio_y[0] = 0;
                src_y = src_h - 2;
            }
            ratio_y[1] = 1 - ratio_y[0]; // y2 - y

            int _dst_i = y * dst_w;

            int _src_row_0 = src_y * src_w;
            int _src_row_1 = _src_row_0 + src_w;

            for (size_t x = x_start; x < x_end; x++)
            {
                float ratio_x[2];
                ratio_x[0] = (float)((x + 0.5) * scale_x - 0.5); // x
                int src_x = (int)ratio_x[0];                     // x1
                ratio_x[0] -= src_x;                             // x - x1

                if (src_x < 0)
                {
                    ratio_x[0] = 0;
                    src_x = 0;
                }
                if (src_x > src_w - 2)
                {
                    ratio_x[0] = 0;
                    src_x = src_w - 2;
                }
                ratio_x[1] = 1 - ratio_x[0]; // x2 - x

                int dst_i = (_dst_i + x) * channel;

                int src_row_0 = (_src_row_0 + src_x) * channel;
                int src_row_1 = (_src_row_1 + src_x) * channel;

                for (int c = 0; c < channel; c++)
                {
                    temp = round(src_image[src_row_0 + c] * ratio_x[1] * ratio_y[1] + src_image[src_row_0 + channel + c] * ratio_x[0] * ratio_y[1] + src_image[src_row_1 + c] * ratio_x[1] * ratio_y[0] + src_image[src_row_1 + channel + c] * ratio_x[0] * ratio_y[0]);
                    dst_image[dst_i + c] = (shift_left > 0) ? (temp << shift_left) : (temp >> -shift_left);
                }
            }
        }
        break;

    case IMAGE_RESIZE_MEAN:
        shift_left -= 2;

        for (size_t y = y_start; y < y_end; y++)
        {
            int _dst_i = y * dst_w;

            float _src_row_0 = rintf(y * scale_y) * src_w;
            float _src_row_1 = _src_row_0 + src_w;

            for (size_t x = x_start; x < x_end; x++)
            {
                int dst_i = (_dst_i + x) * channel;

                int src_row_0 = (_src_row_0 + rintf(x * scale_x)) * channel;
                int src_row_1 = (_src_row_1 + rintf(x * scale_x)) * channel;

                for (size_t c = 0; c < channel; c++)
                {
                    temp = (int)src_image[src_row_0 + c] + (int)src_image[src_row_0 + channel + c] + (int)src_image[src_row_1 + c] + (int)src_image[src_row_1 + channel + c];
                    dst_image[dst_i + c] = (shift_left > 0) ? (temp << shift_left) : (temp >> -shift_left);
                }
            }
        }
        break;

    case IMAGE_RESIZE_NEAREST:
        for (size_t y = y_start; y < y_end; y++)
        {
            int _dst_i = y * dst_w;
            float _src_i = rintf(y * scale_y) * src_w;

            for (size_t x = x_start; x < x_end; x++)
            {
                int dst_i = (_dst_i + x) * channel;
                int src_i = (_src_i + rintf(x * scale_x)) * channel;

                for (size_t c = 0; c < channel; c++)
                {
                    dst_image[dst_i + c] = (shift_left > 0) ? ((T)src_image[src_i + c] << shift_left) : ((T)src_image[src_i + c] >> -shift_left);
                }
            }
        }
        break;

    default:
        break;
    }
}
