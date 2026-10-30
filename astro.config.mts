// @ts-check
import { defineConfig } from "astro/config";
import starlight from "@astrojs/starlight";
import starlightThemeNext from "starlight-theme-next";

export default defineConfig({
  output: "static",
  // redirects: {
  // '/miamore': '/miamore/getting-started',
  // },

  integrations: [
    starlight({
      title: "miamore docs",
      disable404Route: true,
      favicon: "/logo.png",
      head: [
        {
          tag: "link",
          attrs: {
            rel: "icon",
            href: "/logo.png",
            sizes: "32x32",
          },
        },
      ],
      plugins: [starlightThemeNext()],
      customCss: ["./src/styles/style.css"],
      social: [
        {
          icon: "github",
          label: "Github",
          href: "https://github.com/Ametrine-cc",
        },
        {
          icon: "youtube",
          label: "YouTube",
          href: "https://www.youtube.com/@AmetrineFoundation",
        },
        {
          icon: "blueSky",
          label: "Bluesky",
          href: "https://bsky.app/profile/ametrine.cc",
        },
        {
          icon: "mastodon",
          label: "Mastodon",
          href: "https://mastodon.social/@Ametrinefoundation",
        },
      ],
      sidebar: [
        {
          label: "Getting started",
          items: [
            { label: "Getting Started", slug: "miamore/getting-started" },
            { label: "Installation", slug: "miamore/installation" },
            { label: "Examples", slug: "miamore/examples" },
          ],
        },
        {
          label: "Development",
          items: [
            { label: "Development", slug: "miamore/development" },
            {
              label: "Development Extended",
              slug: "miamore/development-extended",
            },
          ],
        },
      ],
    }),
  ],
});
