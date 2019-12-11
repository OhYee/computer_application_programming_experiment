import requests
import threading
import re
import queue
import time
 

class thread (threading.Thread):
    def __init__(self, thread_id, func):
        threading.Thread.__init__(self)
        self.thread_id = thread_id
        self.func = func
        
    def run(self):
        self.func(self.thread_id)


lock_queue = threading.Lock()
lock_map = threading.Lock()

url_queue = queue.Queue(0)

str_int = {}


def get_url():
    ret = None
    lock_queue.acquire()
    if not url_queue.empty():
        ret = url_queue.get()
    lock_queue.release()
    return ret

def record_url(parent, child):
    if child[-3:] in ["css", "gif", "jpg", ".js", "swf", "png"]:
        return

    lock_map.acquire()
    p_id,p_set = str_int.get(parent, (None,None))
    c_id,c_set = str_int.get(child, (None,None))
    if None ==p_id:
        p_id,p_set = str_int[parent] = (len(str_int),set())
    if None ==c_id:
        c_id, c_set = str_int[child] = (len(str_int), set())
        lock_queue.acquire()
        url_queue.put(child)
        lock_queue.release()
    p_set.add(c_id)
    lock_map.release()

    

def get_data(thread_id, url,session):
    print(thread_id, "get", url)
    rep = session.get("http://10.108.106.165/news.sohu.com" +url)
    res = re.findall('http://news.sohu.com([A-Za-z0-9\\-\\_\\%\\&\\?\\/\\=\\.]+)', rep.text)
    for data in res:
        record_url(url, data)
    
def task(thread_id):
    session = requests.Session()
    while 1:
        url = get_url()
        if url == None:
            break
        err_times = 5
        while err_times > 0:
            try:
                print("%6d get %s"%(thread_id, url))
                rep = session.get("http://10.108.106.165/news.sohu.com" +url)
                res = re.findall('http://news.sohu.com([A-Za-z0-9\\-\\_\\%\\&\\?\\/\\=\\.]+)', rep.text)
                for data in res:
                    record_url(url, data)
                break
            except:
                err_times-=1

def save(thread_id):
    last_time = time.time()
    while 1:
        try:
            while time.time() - last_time < 30:
                pass
            last_time = time.time()
            print("\033[1;31m","saving at", time.time(),"\033[0m")
            with open("1.txt", "w") as f:
                lock_map.acquire()
                for key, value in str_int.items():
                    f.write("{} {}\n".format(key, value[0]))
                f.write("\n")
                for parent, parent_data in str_int.items():
                    for child in parent_data[1]:
                        f.write("{} {}\n".format(parent_data[0], child))
                lock_map.release()
        except:
            pass


get_data(-1, "/",requests.Session())

threads = [thread(idx, task) for idx in range(4096)]
sav_thread = thread(-1, save)
for t in threads:
    t.start()
sav_thread.start()

for t in threads:
    t.join()
save(-1)