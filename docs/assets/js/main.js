const navToggle = document.querySelector("#nav-toggle");
const navMenu = document.querySelector("#nav-menu");

if (navToggle && navMenu) {
  navToggle.addEventListener("click", () => {
    const isOpen = navMenu.classList.toggle("is-open");
    navToggle.setAttribute("aria-expanded", String(isOpen));
    navToggle.textContent = isOpen ? "Fechar" : "Menu";
  });

  navMenu.querySelectorAll("a").forEach((link) => {
    link.addEventListener("click", () => {
      navMenu.classList.remove("is-open");
      navToggle.setAttribute("aria-expanded", "false");
      navToggle.textContent = "Menu";
    });
  });
}

const currentFile = (location.pathname.split("/").pop() || "index.html").toLowerCase();
document.querySelectorAll(".nav-menu a").forEach((link) => {
  const href = (link.getAttribute("href") || "").split("#")[0].toLowerCase();
  if (href === currentFile || (currentFile === "" && href === "index.html")) {
    link.classList.add("is-current");
  }
});



const observedSections = [...document.querySelectorAll(".report-section")];
const contentsLinks = document.querySelectorAll(".contents__nav a");

if ("IntersectionObserver" in window && observedSections.length && contentsLinks.length) {
  const sectionObserver = new IntersectionObserver((entries) => {
    entries.forEach((entry) => {
      if (!entry.isIntersecting) return;
      contentsLinks.forEach((link) => {
        link.classList.toggle("is-current", link.hash === `#${entry.target.id}`);
      });
    });
  }, { rootMargin: "-25% 0px -65% 0px" });

  observedSections.forEach((section) => sectionObserver.observe(section));
}
