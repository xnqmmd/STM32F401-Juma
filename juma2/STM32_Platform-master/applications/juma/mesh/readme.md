# mesh
mesh�е�demo��һ���ƿس��򣬼�����ͨ���ֻ�������һ���豸����ָ��Ӷ����������豸��

meshЭ��demo��Ҫ����:
1.�豸��MESH_ID(app.c�ĺ궨��)

2.�㲥�����������ֲ�ͬ�豸(board_name��app.c��)

3.demo�õ��ĸ��豸��MESH_ID�ֱ���Ϊ0x0001,0x0002,0x0004,0x0008.
����Ҳ��ĳɲ�ͬ���Է���ʶ��

### Ч��չʾ



![](./images/mesh1.png) ![](./images/mesh2.png) ![](./images/mesh3.png) ![](./images/mesh4.png)

��Ӧ��android�˳������Ч��չʾ��

��Ƶ���ӣ�
[http://v.qq.com/boke/page/v/0/o/v0190dvi7ro.html](http://v.qq.com/boke/page/v/0/o/v0190dvi7ro.html)

���������
[http://www.52cannon.com/bbs/thread-274-1-1.html](http://www.52cannon.com/bbs/thread-274-1-1.html)

### �������̽���


�����Ҫ����һ�´������̣�

```
1. ϵͳ����(����`ϵͳAPI`��Ҳ��Ӧ�ò��̵ĵ�һ���(ϵͳ�ص��¼�)���൱�ڴ�ͳ��`main()`������) -- on_ready��
2. ����Cannon�������㲥��ַ -- ble_set_adv_param��
3. Cannon��ʼ�����㲥 -- ble_device_start_advertising��
4. �ֻ���APP��Cannon�������ӣ�����ʹ��BLE��������APP��
5. BLE��������APP��Cannon��һЩ���ݣ�
6. Cannon�յ����ݺ󣬴����ص��¼� -- ble_device_on_message��
7. Cannon������ԭ�ⲻ���Ļش����ֻ� -- ble_device_send��
8. �ֻ���Cannon�Ͽ����ӣ�
9. Cannon�����Ͽ������¼� -- ble_device_on_disconnect��
10. Cannon���¿��������㲥 -- ble_device_start_advertising��

```

> ���ס���շ��������ݣ���Ҫ��Ҫ�������ӣ����������ӣ���Ҫ�豸�ȿ����㲥��


### ��

API�ĵ���
[http://www.juma.io/doc/zh/embedded_api/task/](http://www.juma.io/doc/zh/embedded_api/task/)

���л����İ�װָ����
[http://www.juma.io/doc/zh/stm32_platform/cannon_env/](http://www.juma.io/doc/zh/stm32_platform/cannon_env/)

���������
[http://www.juma.io/](http://www.juma.io/)

������̳��
[http://www.52cannon.com/bbs/forum.php](http://www.52cannon.com/bbs/forum.php)

����1000�˽���Ⱥ��
QQ��271927055

���빫�ںţ�
![](./images/1.jpg)