
    static inline void rgb565_to_888(uint16_t in, uint8_t *dst)
    { /*{{{*/
        in = (in & 0xFF) << 8 | (in & 0xFF00) >> 8;
        dst[2] = (in & RGB565_MASK_BLUE) << 3;  // blue
        dst[1] = (in & RGB565_MASK_GREEN) >> 3; // green
        dst[0] = (in & RGB565_MASK_RED) >> 8;   // red

        // dst[0] = (in & 0x1F00) >> 5;
        // dst[1] = ((in & 0x7) << 5) | ((in & 0xE000) >> 11);
        // dst[2] = in & 0xF8;
    } /*}}}*/

    static inline void rgb565_to_888_q16(uint16_t in, int16_t *dst)
    { /*{{{*/
        in = (in & 0xFF) << 8 | (in & 0xFF00) >> 8;
        dst[2] = (in & RGB565_MASK_BLUE) << 3;  // blue
        dst[1] = (in & RGB565_MASK_GREEN) >> 3; // green
        dst[0] = (in & RGB565_MASK_RED) >> 8;   // red

        // dst[0] = (in & 0x1F00) >> 5;
        // dst[1] = ((in & 0x7) << 5) | ((in & 0xE000) >> 11);
        // dst[2] = in & 0xF8;
    } /*}}}*/
    /**@}*/

    /**
     * @brief Convert RGB888 image to RGB565 image
     * 
     * @param in      Resulting RGB565 image
     * @param r       The red channel of the Input RGB888 image 
     * @param g       The green channel of the Input RGB888 image 
     * @param b       The blue channel of the Input RGB888 image
     */
    static inline void rgb888_to_565(uint16_t *in, uint8_t r, uint8_t g, uint8_t b)
    { /*{{{*/
        uint16_t rgb565 = 0;
        rgb565 = ((r >> 3) << 11);
        rgb565 |= ((g >> 2) << 5);
        rgb565 |= (b >> 3);
        rgb565 = (rgb565 & 0xFF) << 8 | (rgb565 & 0xFF00) >> 8;
        *in = rgb565;
    } /*}}}*/

    /**
     * @brief Filter out the resulting boxes whose confidence score is lower than the threshold and convert the boxes to the actual boxes on the original image.((x, y, w, h) -> (x1, y1, x2, y2))
     * 
     * @param score                    Confidence score of the boxes
     * @param offset                   The predicted anchor-based offset
     * @param landmark                 The landmarks corresponding to the box
     * @param width                    Height of the original image
     * @param height                   Width of the original image
     * @param anchor_number            Anchor number of the detection output feature map 
     * @param anchors_size             The anchor size
     * @param score_threshold          Threshold of the confidence score
     * @param stride 
     * @param resized_height_scale 
     * @param resized_width_scale 
     * @param do_regression 
     * @return image_list_t* 
     */
    image_list_t *image_get_valid_boxes(fptp_t *score,
                                        fptp_t *offset,
                                        fptp_t *landmark,
                                        int width,
                                        int height,
                                        int anchor_number,
                                        int *anchors_size,
                                        fptp_t score_threshold,
                                        int stride,
                                        fptp_t resized_height_scale,
                                        fptp_t resized_width_scale,
                                        bool do_regression);
    /**
     * @brief Sort the resulting box lists by their confidence score.
     * 
     * @param image_sorted_list     The sorted box list.
     * @param insert_list           The box list that have not been sorted.
     */
    void image_sort_insert_by_score(image_list_t *image_sorted_list, const image_list_t *insert_list);

    /**
     * @brief Run NMS algorithm 
     * 
     * @param image_list         The input boxes list
     * @param nms_threshold      NMS threshold
     * @param same_area          The flag of boxes with same area
     */
    void image_nms_process(image_list_t *image_list, fptp_t nms_threshold, int same_area);

    /**
     * @brief Resize an image to half size 
     * 
     * @param dimage      The output image
     * @param dw          Width of the output image
     * @param dh          Height of the output image
     * @param dc          Channel of the output image
     * @param simage      Source image
     * @param sw          Width of the source image
     * @param sc          Channel of the source image
     */
    void image_zoom_in_twice(uint8_t *dimage,
                             int dw,
                             int dh,
                             int dc,
                             uint8_t *simage,
                             int sw,
                             int sc);

    /**
     * @brief Resize the image in RGB888 format via bilinear interpolation
     * 
     * @param dst_image    The output image
     * @param src_image    Source image
     * @param dst_w        Width of the output image
     * @param dst_h        Height of the output image
     * @param dst_c        Channel of the output image
     * @param src_w        Width of the source image
     * @param src_h        Height of the source image
     */
    void image_resize_linear(uint8_t *dst_image, uint8_t *src_image, int dst_w, int dst_h, int dst_c, int src_w, int src_h);

    /**
     * @brief Crop， rotate and zoom the image in RGB888 format, 
     * 
     * @param corp_image       The output image
     * @param src_image        Source image
     * @param rotate_angle     Rotate angle
     * @param ratio            scaling ratio
     * @param center           Center of rotation
     */
    void image_cropper(uint8_t *corp_image, uint8_t *src_image, int dst_w, int dst_h, int dst_c, int src_w, int src_h, float rotate_angle, float ratio, float *center);

    /**
     * @brief Convert the rgb565 image to the rgb888 image   
     * 
     * @param m       The output rgb888 image
