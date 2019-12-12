si = {}
pos = 0
on = {}

with open("./result.txt", "w") as ff:
        

    with open("../pagerank/urllist.txt", "r") as f:
        while  f.readable():
            line = f.readline()
            if line == "":
                break
            url, idx = line.split()
            idx = int(idx)

            if url[-3:]in  ["css", "gif", "jpg", ".js", "swf", "png"]:
                si[url] = (-1, idx)
                on[idx] = -1
            else:
                si[url] = (pos, idx)
                on[idx]=pos
                ff.write("{} {}\n".format(url[20:] if len(url)>20 else url[7:], pos))
                pos += 1

    ff.write("\n")

    with open("../pagerank/urlcp.txt", "r") as f:
        while  f.readable():
            line = f.readline()
            if line == "":
                break
            parent, _,child = line.split()
            parent = int(parent)
            child = int(child)

            parent = on.get(parent, -1)
            child = on.get(parent, -1)
            if parent == -1 or child == -1:
                continue
        
            ff.write("{} {}\n".format(parent,child))
