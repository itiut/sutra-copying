package main

import (
	"errors"
	"path/filepath"
)

var ErrNoAvatarURL = errors.New("chat: failed to get avatar URL")

type Avatar interface {
	GetAvatarURL(ChatUser) (string, error)
}

type TryAvatars []Avatar

func (a TryAvatars) GetAvatarURL(u ChatUser) (string, error) {
	for _, avatar := range a {
		if url, err := avatar.GetAvatarURL(u); err == nil {
			return url, nil
		}
	}
	return "", ErrNoAvatarURL
}

type AuthAvatar struct{}

var UseAuthAvatar AuthAvatar

func (_ AuthAvatar) GetAvatarURL(u ChatUser) (string, error) {
	url := u.AvatarURL()
	if url == "" {
		return "", ErrNoAvatarURL
	}
	return url, nil
}

type GravatarAvatar struct{}

var UseGravatar GravatarAvatar

func (_ GravatarAvatar) GetAvatarURL(u ChatUser) (string, error) {
	return "//www.gravatar.com/avatar/" + u.UniqueID(), nil
}

type FileSystemAvatar struct{}

var UseFileSystemAvatar FileSystemAvatar

func (_ FileSystemAvatar) GetAvatarURL(u ChatUser) (string, error) {
	matches, err := filepath.Glob(filepath.Join("avatars", u.UniqueID()+"*"))
	if err != nil || len(matches) == 0 {
		return "", ErrNoAvatarURL
	}
	return "/" + matches[0], nil
}
