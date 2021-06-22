# 匯入函式庫
import cv2
import argparse

# parser
parser = argparse.ArgumentParser()
parser.add_argument("-mode", 
                    '--mode',
                    type=str,
                    help="video or live",
                    default="live")
args = parser.parse_args()
print(args)

# 設定從哪顆鏡頭讀取影像，本範例中為video0
webcam = cv2.VideoCapture(0)
if args.mode == "video":
    # 設定擷取影像的尺寸大小
    webcam.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
    webcam.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)
    # 使用 XVID 編碼
    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    # 建立 VideoWriter 物件，輸出影片至 output.avi
    # FPS 值為 20.0，解析度為 640x360
    out = cv2.VideoWriter('output.avi', fourcc, 20.0, (1280, 720))
while(1):
    # 讀取影像
    return_value, image = webcam.read()

    if args.mode == "video":
        if return_value == True:
            # 寫入影格
            out.write(image)

    cv2.imshow('Live', image)
    # 若按下 q 鍵則離開迴圈
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

out.release()
# 刪除webcam，養成不佔用資源的好習慣
del(webcam)
