
alien.elf:     file format elf32-i386


Disassembly of section .text:

080480b8 <.text>:
 80480b8:	55                   	push   %ebp
 80480b9:	89 e5                	mov    %esp,%ebp
 80480bb:	57                   	push   %edi
 80480bc:	56                   	push   %esi
 80480bd:	53                   	push   %ebx
 80480be:	83 ec 10             	sub    $0x10,%esp
 80480c1:	8b 45 04             	mov    0x4(%ebp),%eax
 80480c4:	8d 7d 08             	lea    0x8(%ebp),%edi
 80480c7:	89 45 f0             	mov    %eax,-0x10(%ebp)
 80480ca:	31 d2                	xor    %edx,%edx
 80480cc:	b8 1a 00 00 00       	mov    $0x1a,%eax
 80480d1:	89 d3                	mov    %edx,%ebx
 80480d3:	89 d1                	mov    %edx,%ecx
 80480d5:	89 d6                	mov    %edx,%esi
 80480d7:	cd 80                	int    $0x80
 80480d9:	85 c0                	test   %eax,%eax
 80480db:	75 5f                	jne    0x804813c
 80480dd:	83 7d f0 02          	cmpl   $0x2,-0x10(%ebp)
 80480e1:	75 59                	jne    0x804813c
 80480e3:	8b 7f 04             	mov    0x4(%edi),%edi
 80480e6:	89 7d e4             	mov    %edi,-0x1c(%ebp)
 80480e9:	c7 45 e8 39 05 00 00 	movl   $0x539,-0x18(%ebp)
 80480f0:	eb 39                	jmp    0x804812b
 80480f2:	69 45 e8 a7 41 00 00 	imul   $0x41a7,-0x18(%ebp),%eax
 80480f9:	89 45 f0             	mov    %eax,-0x10(%ebp)
 80480fc:	be ff ff ff 07       	mov    $0x7ffffff,%esi
 8048101:	31 d2                	xor    %edx,%edx
 8048103:	f7 f6                	div    %esi
 8048105:	89 55 e8             	mov    %edx,-0x18(%ebp)
 8048108:	89 fe                	mov    %edi,%esi
 804810a:	2b 75 e4             	sub    -0x1c(%ebp),%esi
 804810d:	83 fe 1c             	cmp    $0x1c,%esi
 8048110:	77 15                	ja     0x8048127
 8048112:	81 e2 ff 00 00 00    	and    $0xff,%edx
 8048118:	31 d1                	xor    %edx,%ecx
 804811a:	0f b6 86 48 81 04 08 	movzbl 0x8048148(%esi),%eax
 8048121:	39 c1                	cmp    %eax,%ecx
 8048123:	75 02                	jne    0x8048127
 8048125:	eb 03                	jmp    0x804812a
 8048127:	83 cb ff             	or     $0xffffffff,%ebx
 804812a:	47                   	inc    %edi
 804812b:	0f be 0f             	movsbl (%edi),%ecx
 804812e:	84 c9                	test   %cl,%cl
 8048130:	75 c0                	jne    0x80480f2
 8048132:	2b 7d e4             	sub    -0x1c(%ebp),%edi
 8048135:	83 ff 1c             	cmp    $0x1c,%edi
 8048138:	76 02                	jbe    0x804813c
 804813a:	eb 03                	jmp    0x804813f
 804813c:	83 cb ff             	or     $0xffffffff,%ebx
 804813f:	b8 01 00 00 00       	mov    $0x1,%eax
 8048144:	cd 80                	int    $0x80
 8048146:	eb fe                	jmp    0x8048146
 8048148:	78 a3                	js     0x80480ed
 804814a:	65                   	gs
 804814b:	55                   	push   %ebp
 804814c:	ed                   	in     (%dx),%eax
 804814d:	f5                   	cmc    
 804814e:	90                   	nop
 804814f:	da 54 da 5c          	ficoml 0x5c(%edx,%ebx,8)
 8048153:	68 c8 e1 75 d6       	push   $0xd675e1c8
 8048158:	42                   	inc    %edx
 8048159:	b7 7e                	mov    $0x7e,%bh
 804815b:	86 0a                	xchg   %cl,(%edx)
 804815d:	17                   	pop    %ss
 804815e:	92                   	xchg   %eax,%edx
 804815f:	65                   	gs
 8048160:	0c ae                	or     $0xae,%al
 8048162:	47                   	inc    %edi
 8048163:	78 f7                	js     0x804815c
