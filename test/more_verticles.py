
w = 600
h = 400
line_split = 2


'''
[175.0, 150.0]

[475.0, 150.0]

[375.0, 250.0]

[75.0, 250.0]

[175.0, 150.0]

====================

[175.0, 150.0]
[235.0, 150.0]
[295.0, 150.0]
[355.0, 150.0]
[415.0, 150.0]
[475.0, 150.0]



[375.0, 250.0]

[75.0, 250.0]

[175.0, 150.0]

=====================
ls = 5

[x, y]
[x_next, y]

k = (x_next - x) / 5
[x,y]
[x + k * 1, y]
[x + k * 2, y]
[x + k * 3, y]
[x + k * 4, y]
[x + k * 5, y]
[x_next, y]



'''





def get_middle(min, max):
    return (min + max) / 2

def create_vertices():
    ls = 2
    tl_x = get_middle(get_middle(w, w/2), w/2) - 200
    tl_y = get_middle(get_middle(h, h/2), h/2) - 100

    array = [
        [tl_x, tl_y],
        [tl_x + 300, tl_y],
        [tl_x + (300-100), tl_y + 100],
        [tl_x - 100, tl_y + 100],
        [tl_x, tl_y],
    ]
    print("SOURCE:", array)
    print("TMP:")
    tmp = []

            
    for i in range(len(array)-1):
        j1 = 0
        j2 = 0
        if i != len(array)-1:
            k1 = (array[i+1][0] - array[i][0]) / ls
            k2 = (array[i+1][1] - array[i][1]) / ls
            
            print(array[i], '-', array[i+1], 'k1:', k1, 'k2:', k2)
            x = array[i][0]; x_next = array[i+1][0]
            y = array[i][1]; y_next = array[i+1][1]

            v1 = array[i][0]
            v2 = array[i][1]
            for j in range(ls):
                tmp.append([v1, v2])
                v1 += k1
                v2 += k2
                j1 = v1
                j2 = v2
    tmp.append([j1, j2])            
    print(tmp, 'values: ', len(tmp))
create_vertices()
